/**
  *****************************************************************************
  * @file
  * @author Tyler Gamvrelis
  *
  * @ingroup I2cDriver
  * @{
  *****************************************************************************
  */




/********************************* Includes **********************************/
#include "I2cDriver.h"

#if defined(THREADED)
#include "Notification.h"
#endif

#if defined(USE_I2C_SILICON_BUG_FIX)
#include "gpio.h"
#endif



#if defined(USE_I2C_SILICON_BUG_FIX)
namespace{

void generateClocks(uint8_t numClocks, uint8_t sendStopBits);

} // end anonymous namespace
#endif




namespace i2c{
/********************************** I2cDriver ********************************/
// Public
// ----------------------------------------------------------------------------
I2cDriver::I2cDriver(){
    m_max_block_time = 2;
}

#if defined(THREADED)
I2cDriver::I2cDriver(
    OsInterface* os_if,
    I2CInterface* hw_if,
    I2C_HandleTypeDef* i2cHandlePtr
) :
    m_os_if(os_if),
    m_hw_if(hw_if),
    m_i2cHandlePtr(i2cHandlePtr)
{
    if(hw_if != nullptr && i2cHandlePtr != nullptr){
        m_hw_is_initialized = true;
    }

    m_max_block_time = pdMS_TO_TICKS(2);
}
#else

I2cDriver::I2cDriver(
    I2CInterface* hw_if,
    I2C_HandleTypeDef* i2cHandlePtr
) :
    m_hw_if(hw_if),
    m_i2cHandlePtr(i2cHandlePtr)

{
    if(hw_if != nullptr && i2cHandlePtr != nullptr){
        m_hw_is_initialized = true;
    }
}
#endif

void I2cDriver::setMaxBlockTime(uint32_t timeout){
    m_max_block_time = timeout;
}

void I2cDriver::setIOType(IO_Type io_type){
    this->m_io_type = io_type;
}

IO_Type I2cDriver::getIOType(void) const{
    return this->m_io_type;
}

bool I2cDriver::memWrite(
    uint16_t DevAddress,
    uint16_t MemAddress,
    uint16_t MemAddSize,
    uint8_t* pData,
    uint16_t Size
) const
{
#if defined(THREADED)
    uint32_t notification = 0;
    BaseType_t status = pdFALSE;
#endif
    HAL_StatusTypeDef hal_status;
    bool retval = false;

    if(m_hw_is_initialized){
        switch(m_io_type) {
#if defined(THREADED)
            case IO_Type::IT:
                if(m_os_if != nullptr){
                    if(m_hw_if->memWriteIT(
                            m_i2cHandlePtr,
                            DevAddress,
                            MemAddress,
                            MemAddSize,
                            pData,
                            Size
                        ) == HAL_OK
                    )
                    {
                        status = m_os_if->OS_xTaskNotifyWait(
                            0,
                            NOTIFIED_FROM_TX_ISR,
                            &notification,
                            m_max_block_time
                        );

                        if((status == pdTRUE) &&
                           CHECK_NOTIFICATION(notification, NOTIFIED_FROM_TX_ISR))
                        {
                            retval = true;
                        }
                    }
                }
                break;
#endif
            case IO_Type::POLL:
            default:
                hal_status = m_hw_if->memWrite(
                    m_i2cHandlePtr,
                    DevAddress,
                    MemAddress,
                    MemAddSize,
                    pData,
                    Size,
                    m_max_block_time
                );

                retval = (hal_status == HAL_OK);
                break;
        }
#if defined(THREADED)
        if(retval != true){
            m_hw_if->abortTransfer(m_i2cHandlePtr, DevAddress);
#if defined(USE_I2C_SILICON_BUG_FIX)
            // Try fix for flag bit silicon bug
            generateClocks(1, 1);
#endif
        }
#endif
    }

    return retval;
}

bool I2cDriver::memRead(
    uint16_t DevAddress,
    uint16_t MemAddress,
    uint16_t MemAddSize,
    uint8_t* pData,
    uint16_t Size
) const
{
#if defined(THREADED)
    uint32_t notification = 0;
    BaseType_t status = pdFALSE;
#endif
    HAL_StatusTypeDef hal_status;
    bool retval = false;

    if(m_hw_is_initialized){
        switch(m_io_type) {
#if defined(THREADED)
            case IO_Type::IT:
                if(m_os_if != nullptr){
                    if(m_hw_if->memReadIT(
                            m_i2cHandlePtr,
                            DevAddress,
                            MemAddress,
                            MemAddSize,
                            pData,
                            Size
                        ) == HAL_OK
                    )
                    {
                        status = m_os_if->OS_xTaskNotifyWait(
                            0,
                            NOTIFIED_FROM_RX_ISR,
                            &notification,
                            m_max_block_time
                        );

                        if((status == pdTRUE) &&
                           CHECK_NOTIFICATION(notification, NOTIFIED_FROM_RX_ISR))
                        {
                            retval = true;
                        }
                    }
                }
                break;
#endif
            case IO_Type::POLL:
            default:
                hal_status = m_hw_if->memRead(
                    m_i2cHandlePtr,
                    DevAddress,
                    MemAddress,
                    MemAddSize,
                    pData,
                    Size,
                    m_max_block_time
                );

                retval = (hal_status == HAL_OK);
                break;
        }
#if defined(THREADED)
        if(retval != true){
            m_hw_if->abortTransfer(m_i2cHandlePtr, DevAddress);
#if defined(USE_I2C_SILICON_BUG_FIX)
            // Try fix for flag bit silicon bug
            generateClocks(1, 1);
#endif
        }
#endif
    }

    return retval;
}

} // end namespace i2c

namespace{

// Functions
// ----------------------------------------------------------------------------
// We only need these functions for a silicon issue that affects the F446RE and
// not the F767ZI
#if defined(USE_I2C_SILICON_BUG_FIX)
// Note: The following 2 functions are used as a workaround for an issue where the BUSY flag of the
// I2C module is erroneously asserted in the hardware (a silicon bug, essentially). This workaround has
// not been thoroughly tested, but we know it works
//
// Overall, use these functions with EXTREME caution.

/**
  * @brief   Helper function for I2C_ClearBusyFlagErratum.
  * @param   None
  * @return  None
  */
uint8_t wait_for_gpio_state_timeout(GPIO_TypeDef *port,
        uint16_t pin,
        GPIO_PinState state,
        uint8_t timeout){

    uint32_t Tickstart = HAL_GetTick();
    uint8_t ret = 0;
    /* Wait until flag is set */
    while((state != HAL_GPIO_ReadPin(port, pin)) && (1 == ret)){
        /* Check for the timeout */
        if ((timeout == 0U) || (HAL_GetTick() - Tickstart >= timeout)){
            ret = 0;
        }
        asm("nop");
    }
    return ret;
}

/**
  * @brief   This function big-bangs the I2C master clock
  *          https://electronics.stackexchange.com/questions/267972/i2c-busy-flag-strange-behaviour/281046#281046
  *          https://community.st.com/thread/35884-cant-reset-i2c-in-stm32f407-to-release-i2c-lines
  *          https://electronics.stackexchange.com/questions/272427/stm32-busy-flag-is-set-after-i2c-initialization
  *          http://www.st.com/content/ccc/resource/technical/document/errata_sheet/f5/50/c9/46/56/db/4a/f6/CD00197763.pdf/files/CD00197763.pdf/jcr:content/translations/en.CD00197763.pdf
  * @param   numClocks The number of times to cycle the I2C master clock
  * @param   sendStopBits 1 if stop bits are to be sent on SDA
  * @return  None
  */
void generateClocks(uint8_t numClocks, uint8_t sendStopBits){
    static struct I2C_Module{
        I2C_HandleTypeDef*   instance;
        uint16_t            sdaPin;
        GPIO_TypeDef*       sdaPort;
        uint16_t            sclPin;
        GPIO_TypeDef*       sclPort;
    }i2cmodule = {&hi2c1, GPIO_PIN_7, GPIOB, GPIO_PIN_6, GPIOB};
    static struct I2C_Module* i2c = &i2cmodule;
    static uint8_t timeout = 1;

    GPIO_InitTypeDef GPIO_InitStructure;

    I2C_HandleTypeDef* handler = NULL;

    handler = i2c->instance;

    // 1. Clear PE bit.
    CLEAR_BIT(handler->Instance->CR1, I2C_CR1_PE);

    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    GPIO_InitStructure.Pin = i2c->sclPin;
    HAL_GPIO_Init(i2c->sclPort, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = i2c->sdaPin;
    HAL_GPIO_Init(i2c->sdaPort, &GPIO_InitStructure);

    for(uint8_t i = 0; i < numClocks; i++){
        // 3. Check SCL and SDA High level in GPIOx_IDR.
        if(sendStopBits){HAL_GPIO_WritePin(i2c->sdaPort, i2c->sdaPin, GPIO_PIN_SET);}
        HAL_GPIO_WritePin(i2c->sclPort, i2c->sclPin, GPIO_PIN_SET);

        wait_for_gpio_state_timeout(i2c->sclPort, i2c->sclPin, GPIO_PIN_SET, timeout);
        if(sendStopBits){wait_for_gpio_state_timeout(i2c->sdaPort, i2c->sdaPin, GPIO_PIN_SET, timeout);}

        // 4. Configure the SDA I/O as General Purpose Output Open-Drain, Low level (Write 0 to GPIOx_ODR).
        if(sendStopBits){
            HAL_GPIO_WritePin(i2c->sdaPort, i2c->sdaPin, GPIO_PIN_RESET);
            wait_for_gpio_state_timeout(i2c->sdaPort, i2c->sdaPin, GPIO_PIN_RESET, timeout); // 5. Check SDA Low level in GPIOx_IDR
        }

        // 6. Configure the SCL I/O as General Purpose Output Open-Drain, Low level (Write 0 to GPIOx_ODR).
        HAL_GPIO_WritePin(i2c->sclPort, i2c->sclPin, GPIO_PIN_RESET);
        wait_for_gpio_state_timeout(i2c->sclPort, i2c->sclPin, GPIO_PIN_RESET, timeout); // 7. Check SCL Low level in GPIOx_IDR.

        // 8. Configure the SCL I/O as General Purpose Output Open-Drain, High level (Write 1 to GPIOx_ODR).
        HAL_GPIO_WritePin(i2c->sclPort, i2c->sclPin, GPIO_PIN_SET);
        wait_for_gpio_state_timeout(i2c->sclPort, i2c->sclPin, GPIO_PIN_SET, timeout); // 9. Check SCL High level in GPIOx_IDR.

        // 10. Configure the SDA I/O as General Purpose Output Open-Drain , High level (Write 1 to GPIOx_ODR).
        if(sendStopBits){
            HAL_GPIO_WritePin(i2c->sdaPort, i2c->sdaPin, GPIO_PIN_SET);
            wait_for_gpio_state_timeout(i2c->sdaPort, i2c->sdaPin, GPIO_PIN_SET, timeout); // 11. Check SDA High level in GPIOx_IDR.
        }
    }

    // 12. Configure the SCL and SDA I/Os as Alternate function Open-Drain.
    GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStructure.Alternate = GPIO_AF4_I2C1;

    GPIO_InitStructure.Pin = i2c->sclPin;
    HAL_GPIO_Init(i2c->sclPort, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = i2c->sdaPin;
    HAL_GPIO_Init(i2c->sdaPort, &GPIO_InitStructure);

    // 13. Set SWRST bit in I2Cx_CR1 register.
    SET_BIT(handler->Instance->CR1, I2C_CR1_SWRST);
    asm("nop");

    /* 14. Clear SWRST bit in I2Cx_CR1 register. */
    CLEAR_BIT(handler->Instance->CR1, I2C_CR1_SWRST);
    asm("nop");

    /* 15. Enable the I2C peripheral by setting the PE bit in I2Cx_CR1 register */
    SET_BIT(handler->Instance->CR1, I2C_CR1_PE);
    asm("nop");

    HAL_I2C_Init(handler);
}
#endif

} // end anonymous namespace


/**
 * @}
 */
