/**
  ******************************************************************************
  * @file
  * @author Izaak
  * @author Jenny
  * @author Tyler
  *
  * @defgroup MPU6050
  * @brief Interfaces for reading data from a MPU6050 sensor, as well as
  *        setting control registers.
  * @{
  ******************************************************************************
  */




#ifndef MPU6050_H
#define MPU6050_H




/********************************* Includes **********************************/
#include <stdint.h>
#include "I2cDriver.h"




/********************************* MPU6050 ***********************************/
namespace imu{
// Classes and structs
// ----------------------------------------------------------------------------
/** @brief Data measured by the IMU */
typedef struct{
    float vx; /**< x-axis angular velocity read from sensor */
    float vy; /**< y-axis angular velocity read from sensor */
    float vz; /**< z-axis angular velocity read from sensor */
    float ax; /**< x-axis acceleration read from sensor     */
    float ay; /**< y-axis acceleration read from sensor     */
    float az; /**< z-axis acceleration read from sensor     */
}IMUStruct_t;


class MPU6050 {
public:
    /**
     * @brief The constructor for the MPU6050 class, which initializes non-I/O
     *        members
     * @param driver Pointer to the I2C driver handling the low-level interface
     */
    MPU6050(i2c::I2cDriver* driver);


    /**
     * @brief The MPU6050 destructor
     */
    ~MPU6050() {}

    /**
     * @brief This function is used to initialize all aspects of the IMU
     *        which require I/O
     */
    void init();

    /**
     * @brief Sets the offsets of the sensor. Note that a lower setting
     *        implies smaller bandwidth but higher signal delay
     * @param lpf The setting being used for the built-in DLPF. Must be
     *        less than or equal to 6 (6 -> 5 Hz bandwidth, 0 -> about 260
     *        Hz bandwidth)
     * @return true if successful, otherwise false
     */
    bool set_dlpf(uint8_t lpf);

    /**
     * @brief Reads the the angular velocity in the x-, y-, and z-axes from the
     *        gyroscope
     * @return true if successful, otherwise false
     */
    bool read_gyroscope();

    /**
     * @brief Reads the acceleration along the x-, y-, and z-axes from the
     *        accelerometer
     * @return true if successful, otherwise false
     */
    bool read_accelerometer();

    /**
     * @brief Retrieves state information from the IMU
     * @return Data the IMU has measured from the gyroscope and accelerometer
     */
    IMUStruct_t get_data();

private:
    /**
     * @brief Writes to a register from the MPU6050
     * @param reg_addr uint8_t address of the register
     * @param data uint8_t data to be written
     * @return true if successful, otherwise false
     */
    bool write_reg(
        uint8_t reg_addr,
        uint8_t data
    );

    /**
     * @brief Reads 1 or more bytes from the sensor's register bank into a
     *        provided buffer
     * @param reg_addr Address of the register to start reading from
     * @param p_data Address of received data buffer
     * @param num_bytes Size of the received data buffer
     * @return true if successful, otherwise false
     */
    bool read_data(
        uint8_t reg_addr,
        const uint8_t* p_data,
        uint8_t num_bytes
    );

    const i2c::I2cDriver* m_driver; /**< I2C driver used for this sensor instance */
    IMUStruct_t m_data; /**< Data measured by IMU */
};

} // end namespace imu


/**
 * @}
 */

#endif /* MPU6050_H_ */
