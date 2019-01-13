/**
  *****************************************************************************
  * @file I2cDriver.h
  * @author Tyler Gamvrelis
  *
  * @defgroup I2CDriver
  * @brief Manages the usage of a particular I2C, taking care of
  *        hardware-level calls, OS-level calls, and passing up statuses
  * @{
  *****************************************************************************
  */




#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H




/********************************* Includes **********************************/
#include "I2CInterface.h"

#if defined(THREADED)
#include "cmsis_os.h"
#include "OsInterface.h"
using os::OsInterface;
#endif




/********************************* I2CDriver *********************************/
namespace i2c{

// Classes and structs
// ----------------------------------------------------------------------------
/**
 * @class I2cDriver Manages the usage of a particular I2C, taking care of
 *        hardware-level calls, OS-level calls, and passing up statuses. OS
 *        support is selected at compile time based on whether the THREADED
 *        macro is defined
 */
class I2cDriver{
public:
    I2cDriver();

#if defined(THREADED)
    /**
     * @brief Initializes the handle to the low-level hardware routines,
     *        associates a particular I2C module on the board with this
     *        driver, and initializes the handle to the OS for system calls
     * @param os_if Pointer to the object handling the calls to the OS
     * @param hw_if Pointer to the hardware-facing object handling the
     *        low-level I2C routines
     * @param i2cHandlePtr Pointer to a structure that contains
     *        the configuration information for the desired I2C module
     */
    I2cDriver(
        OsInterface* os_if,
        I2CInterface* hw_if,
        I2C_HandleTypeDef* i2cHandlePtr
    );
#else
    /**
     * @brief Initializes the handle to the low-level hardware routines, and
     *        associates a particular I2C module on the board with this driver
     * @param hw_if Pointer to the hardware-facing object handling the
     *        low-level I2C routines
     * @param i2cHandlePtr Pointer to a structure that contains
     *        the configuration information for the desired I2C module
     */
    I2cDriver(
        I2CInterface* hw_if,
        I2C_HandleTypeDef* i2cHandlePtr
    );
#endif

    ~I2cDriver() {}

    /**
     * @brief Sets data transfer timeout for this driver instance
     * @param timeout The maximum time the caller will block on a data transfer
     */
    void setMaxBlockTime(uint32_t timeout);

    /**
     * @brief Configures the driver to use a particular IO type. This is used
     *        to change it between using blocking and asynchronous transfers
     * @param io_type The type of IO to be used by the driver
     */
    void setIOType(IO_Type io_type);

    /**
     * @brief Returns the IO type currently being used by the driver
     * @return The IO type currently being used by the driver
     */
    IO_Type getIOType(void) const;

    /**
     * @brief  Instruct the driver to transmit data from the I2C that was set
     *         by setI2CInterface, and using the IO transfer mode set by
     *         setIOType
     * @param  DevAddress Target device address
     * @param  MemAddress Internal memory address
     * @param  MemAddSize Size of internal memory address
     * @param  pData Pointer to data buffer
     * @param  Size Amount of data to be sent
     * @return True if the transfer succeeded, otherwise false
     * @note   Some reasons why false may be returned include:
     *           -# Incomplete initialization of the driver
     *           -# I2CInterface returns an error upon requesting a transfer
     *           -# OS block time is exceeded
     */
    bool memWrite(
        uint16_t DevAddress,
        uint16_t MemAddress,
        uint16_t MemAddSize,
        uint8_t* pData,
        uint16_t Size
    ) const;

    /**
     * @brief  Instruct the driver to receive data from the I2C that was set
     *         by setI2CInterface, and using the IO transfer mode set by
     *         setIOType.
     * @param  DevAddress Target device address
     * @param  MemAddress Internal memory address
     * @param  MemAddSize Size of internal memory address
     * @param  pData Pointer to data buffer
     * @param  Size Amount of data to be sent
     * @return True if the transfer succeeded, otherwise false
     * @note   Some reasons why false may be returned include:
     *           -# Incomplete initialization of the driver
     *           -# I2CInterface returns an error upon requesting a transfer
     *           -# OS block time is exceeded
     */
    bool memRead(
        uint16_t DevAddress,
        uint16_t MemAddress,
        uint16_t MemAddSize,
        uint8_t* pData,
        uint16_t Size
    ) const;

private:
    /**
     * @brief IO Type used by the driver
     */
    IO_Type m_io_type = IO_Type::POLL;

#if defined(THREADED)
    /** @brief Pointer to the object handling system calls to the OS */
    const OsInterface* m_os_if = nullptr;
#endif

    /**
     * @brief Pointer to the object handling direct calls to the I2C hardware
     */
    const I2CInterface* m_hw_if = nullptr;

    /**
     * @brief Address of the container for the I2C module associated with this
     *        object
     */
    const I2C_HandleTypeDef* m_i2cHandlePtr = nullptr;

    /**
     * @brief true if the I2CInterface has been set and its I2C_HandleTypeDef
     *        pointer has been set, otherwise false
     */
    bool m_hw_is_initialized = false;

    /** @brief Maximum permitted time for blocking on a data transfer */
    TickType_t m_max_block_time;
};

} // end namespace i2c




/**
 * @}
 */

#endif /* I2C_DRIVER_H */
