/**
  *****************************************************************************
  * @file
  * @author Izaak
  * @author Tyler
  * @author Jenny
  *
  * @ingroup MPU6050
  * @{
  *****************************************************************************
  */




/********************************* Includes **********************************/
#include "MPU6050.h"
#include <math.h>




/******************************** File-local *********************************/
namespace {
// Constants
// ----------------------------------------------------------------------------
constexpr float g = 9.81;
constexpr uint8_t I2C_ID = 0b11010000;

// Unit conversion constants
/** Divide by this to get degrees per second from the gyroscope readings */
constexpr float IMU_GY_RANGE = 131.0;

/** Divide to get units of g from the accelerometer readings*/
constexpr float ACC_RANGE = 16384.0;

// Control register addresses
constexpr uint8_t REG_DLPF = 0x1A;
constexpr uint8_t REG_GYRO_CONFIG = 0x1B;
constexpr uint8_t REG_ACCEL_CONFIG = 0x1C;
constexpr uint8_t REG_I2C_MST_CTRL = 0x24;
constexpr uint8_t REG_SMPLRT_DIV = 0x19;

// Measurement register addresses
constexpr uint8_t REG_ACCEL_XOUT_H = 0x3B;
constexpr uint8_t REG_GYRO_XOUT_H = 0x43;
constexpr uint8_t REG_PWR_MGMT_1 = 0x6B;
constexpr uint8_t REG_PWR_MGMT_2 = 0x6C;

// Sample rate divider setting
constexpr uint8_t CLOCK_DIV_296 = 0x4;

} // end anonymous namespace




/********************************* MPU6050 ***********************************/
namespace imu{
// Public
// ----------------------------------------------------------------------------
MPU6050::MPU6050(i2c::I2cDriver* driver)
    : m_driver(driver)
{
    // Initialize all the variables
    this->m_data = {NAN};
}

void MPU6050::init(){
    MPU6050::write_reg(REG_I2C_MST_CTRL, 0b00001101); //0b00001101 is FAST MODE = 400 kHz
    MPU6050::write_reg(REG_ACCEL_CONFIG, 0);
    MPU6050::write_reg(REG_GYRO_CONFIG, 0);
    MPU6050::write_reg(REG_PWR_MGMT_1, 0);
    MPU6050::write_reg(REG_PWR_MGMT_2, 0);
    MPU6050::write_reg(REG_SMPLRT_DIV, CLOCK_DIV_296);
}

bool MPU6050::set_dlpf(uint8_t lpf){
    bool retval = false;
    if(lpf <= 6){
        uint8_t cur_val;
        const uint8_t bitmask = 0b00000111;

        MPU6050::read_data(REG_DLPF, &cur_val, 1);

        // Note that this register also contains fsync data which should be
        // preserved when the DLPF setting is modified
        cur_val = (cur_val & (~bitmask)) | lpf;
        if(MPU6050::write_reg(REG_DLPF, cur_val)){
            retval = true;
        }
    }
    return retval;
}

bool MPU6050::read_gyroscope(){
    uint8_t buff[6];
    bool success = MPU6050::read_data(REG_GYRO_XOUT_H, buff, sizeof(buff));
    if(success){
        int16_t x = static_cast<uint16_t>((buff[0] << 8) | buff[1]);
        int16_t y = static_cast<uint16_t>((buff[2] << 8) | buff[3]);
        int16_t z = static_cast<uint16_t>((buff[4] << 8) | buff[5]);

        this->m_data.vx = static_cast<float>(x) / IMU_GY_RANGE;
        this->m_data.vy = static_cast<float>(y) / IMU_GY_RANGE;
        this->m_data.vz = static_cast<float>(z) / IMU_GY_RANGE;
    }
    return success;
}

bool MPU6050::read_accelerometer(){
    uint8_t buff[6];
    bool success = MPU6050::read_data(REG_ACCEL_XOUT_H, buff, sizeof(buff));
    if(success){
        int16_t x = static_cast<uint16_t>((buff[0] << 8)| buff[1]);
        int16_t y = static_cast<uint16_t>((buff[2] << 8)| buff[3]);
        int16_t z = static_cast<uint16_t>((buff[4] << 8)| buff[5]);

        this->m_data.ax = -(x * g / ACC_RANGE);
        this->m_data.ay = -(y * g / ACC_RANGE);
        this->m_data.az = -(z * g / ACC_RANGE);
    }
    return success;
}

IMUStruct_t MPU6050::get_data(){
    return m_data;
}

// Private
// ----------------------------------------------------------------------------
bool MPU6050::write_reg(
    uint8_t reg_addr,
    uint8_t data
)
{
    constexpr uint8_t addr_size = 1;
    constexpr uint8_t num_bytes = 1;
    return m_driver->memWrite(I2C_ID, reg_addr, addr_size, &data, num_bytes);
}

bool MPU6050::read_data(
    uint8_t reg_addr,
    const uint8_t* p_data,
    uint8_t num_bytes
)
{
    constexpr uint8_t addr_size = 1;
    return m_driver->memRead(
        I2C_ID,
        reg_addr,
        addr_size,
        const_cast<uint8_t*>(p_data),
        num_bytes
    );
}

} // end namespace imu

/**
 * @}
 */
