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
        }
#endif
    }

    return retval;
}

} // end namespace i2c




/**
 * @}
 */
