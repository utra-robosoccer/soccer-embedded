/**
 *****************************************************************************
 * @file    HalI2CInterface.h
 * @author  Hannah L
 * @brief   Defines the HALI2CInterface class, which calls HAL functions related to I2C
 *
 * @defgroup HalI2CInterface
 * @ingroup  I2C
 * @{
 *****************************************************************************
 */

#ifndef COMMON_HALI2CINTERFACE_H
#define COMMON_HALI2CINTERFACE_H

/********************************* Includes **********************************/
#include "I2CInterface.h"
#include "SystemConf.h"

/****************************** HAL I2C Interface ****************************/
namespace i2c{
/**
 * @class Concrete HAL implementation of the abstract I2CInterface class, to be
 *        used in production builds
 */
class HalI2CInterface: public I2CInterface {
public:
    HalI2CInterface();
    ~HalI2CInterface();

    HAL_StatusTypeDef memWrite(
        const I2C_HandleTypeDef* hi2c,
        uint16_t DevAddress,
        uint16_t MemAddress,
        uint16_t MemAddSize,
        uint8_t* pData,
        uint16_t Size,
        uint32_t Timeout
    ) const override final;

    HAL_StatusTypeDef memRead(
        const I2C_HandleTypeDef* hi2c,
        uint16_t DevAddress,
        uint16_t MemAddress,
        uint16_t MemAddSize,
        uint8_t* pData,
        uint16_t Size,
        uint32_t Timeout
    ) const override final;

#if defined(THREADED)
    HAL_StatusTypeDef memWriteIT(
        const I2C_HandleTypeDef* hi2c,
        uint16_t DevAddress,
        uint16_t MemAddress,
        uint16_t MemAddSize,
        uint8_t* pData,
        uint16_t Size
    ) const override final;

    HAL_StatusTypeDef memReadIT(
        const I2C_HandleTypeDef* hi2c,
        uint16_t DevAddress,
        uint16_t MemAddress,
        uint16_t MemAddSize,
        uint8_t* pData,
        uint16_t Size
    ) const override final;

    virtual HAL_StatusTypeDef abortTransfer(
        const I2C_HandleTypeDef* hi2c,
        uint16_t DevAddress
    ) const override final;
#endif
};

} // end namespace i2c

/**
 * @}
 */

#endif /* COMMON_HALI2CINTERFACE_H_ */
