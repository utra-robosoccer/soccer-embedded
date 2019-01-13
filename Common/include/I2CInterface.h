/**
 *****************************************************************************
 * @file    I2CInterface.h
 * @author  Hannah L
 *
 * @defgroup I2CInterface
 * @ingroup  I2C
 * @{
 *****************************************************************************
 */

#ifndef COMMON_INCLUDE_I2CINTERFACE_H
#define COMMON_INCLUDE_I2CINTERFACE_H

/********************************* Includes **********************************/
#include <stdint.h>
#include "SystemConf.h"
#include "i2c.h"

/******************************* I2C Interface *******************************/
namespace i2c {
// Types & enums
// ----------------------------------------------------------------------------
/**
 * @brief Enumerates the IO types supported by a class which implements the
 *        UartInterface class
 */
enum class IO_Type{
    POLL /**< Polled IO          */
#if defined(THREADED)
    ,
    IT, /**< Interrupt-driven IO */
#endif
};


// Classes and Structs
/**
 * @class I2CInterface Abstract class defining the interface that a
 *        hardware-facing I2C object must have. This object takes care of
 *        directly interfacing with the hardware as it is instructed, without
 *        knowledge of the application logic
 */
class I2CInterface {
public:
    virtual ~I2CInterface() {}

    /**
     * @brief  Write an amount of data in blocking mode to a specific memory
     *         address
     * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
     *         the configuration information for the specified I2C
     * @param  DevAddress Target device address
     * @param  MemAddress Internal memory address
     * @param  MemAddSize Size of internal memory address
     * @param  pData Pointer to data buffer
     * @param  Size Amount of data to be sent
     * @param  Timeout Timeout duration
     * @retval HAL status
     */
    virtual HAL_StatusTypeDef memWrite(
        const I2C_HandleTypeDef* hi2c,
        uint16_t DevAddress,
        uint16_t MemAddress,
        uint16_t MemAddSize,
        uint8_t* pData,
        uint16_t Size,
        uint32_t Timeout
    ) const = 0;

    /**
     * @brief  Read an amount of data in blocking mode from a specific memory
     *         address
     * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
     *         the configuration information for the specified I2C
     * @param  DevAddress Target device address
     * @param  MemAddress Internal memory address
     * @param  MemAddSize Size of internal memory address
     * @param  pData Pointer to data buffer
     * @param  Size Amount of data to be sent
     * @param  Timeout Timeout duration
     * @retval HAL status
     */
    virtual HAL_StatusTypeDef memRead(
        const I2C_HandleTypeDef* hi2c,
        uint16_t DevAddress,
        uint16_t MemAddress,
        uint16_t MemAddSize,
        uint8_t* pData,
        uint16_t Size,
        uint32_t Timeout
    ) const = 0;

#if defined(THREADED)
    /**
     * @brief  Write an amount of data in non-blocking mode with Interrupt to a
     *         specific memory address
     * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
     *         the configuration information for the specified I2C
     * @param  DevAddress Target device address
     * @param  MemAddress Internal memory address
     * @param  MemAddSize Size of internal memory address
     * @param  pData Pointer to data buffer
     * @param  Size Amount of data to be sent
     * @retval HAL status
     */
    virtual HAL_StatusTypeDef memWriteIT(
        const I2C_HandleTypeDef* hi2c,
        uint16_t DevAddress,
        uint16_t MemAddress,
        uint16_t MemAddSize,
        uint8_t* pData,
        uint16_t Size
    ) const = 0;

    /**
     * @brief  Read an amount of data in non-blocking mode with Interrupt from
     *         a specific memory address
     * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
     *         the configuration information for the specified I2C
     * @param  DevAddress Target device address
     * @param  MemAddress Internal memory address
     * @param  MemAddSize Size of internal memory address
     * @param  pData Pointer to data buffer
     * @param  Size Amount of data to be sent
     * @retval HAL status
     */
    virtual HAL_StatusTypeDef memReadIT(
        const I2C_HandleTypeDef* hi2c,
        uint16_t DevAddress,
        uint16_t MemAddress,
        uint16_t MemAddSize,
        uint8_t* pData,
        uint16_t Size
    ) const = 0;

    /**
     * @brief  Abort an asynchronous transfer
     * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
     *         the configuration information for the specified I2C
     * @param  DevAddress Target device address
     * @retval HAL status
     */
    virtual HAL_StatusTypeDef abortTransfer(
        const I2C_HandleTypeDef* hi2c,
        uint16_t DevAddress
    ) const = 0;
#endif
};

} // end namespace i2c

#endif /* COMMON_INCLUDE_I2CINTERFACE_H */
