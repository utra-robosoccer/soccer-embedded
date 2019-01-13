/**
 *****************************************************************************
 * @file    HalI2CInterface.cpp
 * @author  Hannah
 * @brief   Performs HAL related functions for I2C Interface
 *
 * @defgroup HalI2CInterface
 * @ingroup  I2C
 * @brief    HAL related functions for I2C Interface
 * @{
 *****************************************************************************
 */

/********************************* Includes **********************************/
#include "HalI2CInterface.h"


namespace i2c{
/**************************** HAL I2C Interface ******************************/
// Public
HalI2CInterface::HalI2CInterface() {}
HalI2CInterface::~HalI2CInterface() {}

HAL_StatusTypeDef HalI2CInterface::memWrite(
    const I2C_HandleTypeDef* hi2c,
    uint16_t DevAddress,
    uint16_t MemAddress,
    uint16_t MemAddSize,
    uint8_t* pData,
    uint16_t Size,
    uint32_t Timeout
) const
{
    return HAL_I2C_Mem_Write(
        const_cast<I2C_HandleTypeDef*>(hi2c),
        DevAddress,
        MemAddress,
        MemAddSize,
        pData,
        Size,
        Timeout
    );
}

HAL_StatusTypeDef HalI2CInterface::memRead(
    const I2C_HandleTypeDef* hi2c,
    uint16_t DevAddress,
    uint16_t MemAddress,
    uint16_t MemAddSize,
    uint8_t* pData,
    uint16_t Size,
    uint32_t Timeout
) const
{
    return HAL_I2C_Mem_Read(
        const_cast<I2C_HandleTypeDef*>(hi2c),
        DevAddress,
        MemAddress,
        MemAddSize,
        pData,
        Size,
        Timeout
    );
}

#if defined(THREADED)
HAL_StatusTypeDef HalI2CInterface::memWriteIT(
    const I2C_HandleTypeDef* hi2c,
    uint16_t DevAddress,
    uint16_t MemAddress,
    uint16_t MemAddSize,
    uint8_t* pData,
    uint16_t Size
) const
{
    return HAL_I2C_Mem_Write_IT(
        const_cast<I2C_HandleTypeDef*>(hi2c),
        DevAddress,
        MemAddress,
        MemAddSize,
        pData,
        Size
    );
}

HAL_StatusTypeDef HalI2CInterface::memReadIT(
    const I2C_HandleTypeDef* hi2c,
    uint16_t DevAddress,
    uint16_t MemAddress,
    uint16_t MemAddSize,
    uint8_t* pData,
    uint16_t Size
) const
{
    return HAL_I2C_Mem_Read_IT(
        const_cast<I2C_HandleTypeDef*>(hi2c),
        DevAddress,
        MemAddress,
        MemAddSize,
        pData,
        Size
    );
}

HAL_StatusTypeDef HalI2CInterface::abortTransfer(
    const I2C_HandleTypeDef* hi2c,
    uint16_t DevAddress
) const
{
    return HAL_I2C_Master_Abort_IT(
        const_cast<I2C_HandleTypeDef*>(hi2c),
        DevAddress
    );
}
#endif

} // end namespace i2c

/**
 * @}
 */
