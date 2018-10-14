/**
  *****************************************************************************
  * @file    Motor_test.cpp
  * @author  Tyler Gamvrelis
  *
  * @defgroup Motor_Test
  * @ingroup  Dynamixel
  * @brief    Motor test driver
  * @{
  *****************************************************************************
  */




/********************************* Includes **********************************/
#include "MockMotor.h"

#include "MockUartInterface.h"
#include "MockOsInterface.h"
#include "MockGpioInterface.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;

using uart::UartDriver;

using mocks::MockMotor;
using mocks::MockOsInterface;
using mocks::MockUartInterface;
using mocks::MockGpioInterface;

using dynamixel::Motor;
using dynamixel::DaisyChainParams;
using dynamixel::DaisyChain;
using dynamixel::ResolutionDivider;
using dynamixel::VoltageLimit;
using dynamixel::StatusReturnLevel;
using dynamixel::AlarmType;
using dynamixel::AlarmCondition;




/******************************** File-local *********************************/
namespace{
// Variables
// ----------------------------------------------------------------------------
MockUartInterface uart;
MockOsInterface os;
MockGpioInterface gpio;
UART_HandleTypeDef UARTx = {0};
UartDriver UARTxDriver(&os, &uart, &UARTx);

GPIO_TypeDef dataDirPort;

DaisyChainParams p;



// Classes & structs
// ----------------------------------------------------------------------------
class MotorTest : public ::testing::Test {
protected:
    void SetUp() override {
        p.uartDriver = &UARTxDriver;
        p.gpioif = &gpio;
        p.dataDirPort = &dataDirPort;
        p.dataDirPinNum = 1;
    }
};




// Functions
// ----------------------------------------------------------------------------
TEST_F(MotorTest, CanBeCreated){
    DaisyChain chain(p);
    MockMotor m1(1, &chain, ResolutionDivider::AX12A);
    MockMotor m2(1, &chain, ResolutionDivider::MX28);
}

TEST_F(MotorTest, CanResetMotor){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.reset();
}

TEST_F(MotorTest, setIdBoundsCheckPasses){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.setId(10);

    ASSERT_FALSE(m.setId(0xFD));
    ASSERT_FALSE(m.setId(0xFF));
}

TEST_F(MotorTest, setReturnDelayTimeBoundsCheckPasses){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.setReturnDelayTime(150);

    ASSERT_FALSE(m.setReturnDelayTime(0));
    ASSERT_FALSE(m.setReturnDelayTime(510));
}

TEST_F(MotorTest, setCWAngleLimitBoundsCheckPasses){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.setCwAngleLimit(dynamixel::MIN_ANGLE);

    ASSERT_FALSE(m.setCwAngleLimit(dynamixel::MIN_ANGLE - 1));
    ASSERT_FALSE(m.setCwAngleLimit(dynamixel::MAX_ANGLE + 1));
}

TEST_F(MotorTest, setCCWAngleLimitBoundsCheckPasses){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.setCcwAngleLimit(dynamixel::MAX_ANGLE);

    ASSERT_FALSE(m.setCcwAngleLimit(dynamixel::MIN_ANGLE - 1));
    ASSERT_FALSE(m.setCcwAngleLimit(dynamixel::MAX_ANGLE + 1));
}

TEST_F(MotorTest, setVoltageLimitsBoundsCheckPasses){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.setVoltageLimit(VoltageLimit::HIGHEST, dynamixel::MAX_VOLTAGE);
    m.setVoltageLimit(VoltageLimit::LOWEST, dynamixel::MIN_VOLTAGE);

    ASSERT_FALSE(
        m.setVoltageLimit(VoltageLimit::HIGHEST, dynamixel::MAX_VOLTAGE + 1)
    );

    ASSERT_FALSE(
        m.setVoltageLimit(VoltageLimit::LOWEST, dynamixel::MIN_VOLTAGE - 1)
    );
}

TEST_F(MotorTest, setMaxTorqueBoundsCheckPasses){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.setMaxTorque(100.0);

    ASSERT_FALSE(m.setMaxTorque(-1.0));
    ASSERT_FALSE(m.setMaxTorque(101.0));
}

TEST_F(MotorTest, setStatusReturnLevelBoundsCheckPasses){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.setStatusReturnLevel(StatusReturnLevel::PING_ONLY);
    m.setStatusReturnLevel(StatusReturnLevel::READS_ONLY);
    m.setStatusReturnLevel(StatusReturnLevel::ALL_COMMANDS);

    ASSERT_FALSE(m.setStatusReturnLevel(StatusReturnLevel::NUM_LEVELS));
}

TEST_F(MotorTest, setAlarmBoundsCheckPasses){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.setAlarm(AlarmType::LED, AlarmCondition::INPUT_VOLTAGE_ERR);
    m.setAlarm(AlarmType::SHUTDOWN, AlarmCondition::OVERHEATING_ERR);

    ASSERT_FALSE(m.setAlarm(AlarmType::LED, AlarmCondition::NUM_CONDITIONS));

    ASSERT_FALSE(
        m.setAlarm(AlarmType::NUM_TYPES, AlarmCondition::OVERHEATING_ERR)
    );
}

TEST_F(MotorTest, CanEnableTorque){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.enableTorque(true);
    m.enableTorque(false);
}

TEST_F(MotorTest, CanEnableLed){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.enableLed(true);
    m.enableLed(false);
}

TEST_F(MotorTest, setGoalPositionBoundsCheckPasses){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.setGoalPosition(150.0);

    ASSERT_FALSE(m.setGoalPosition(dynamixel::MIN_ANGLE - 1));
    ASSERT_FALSE(m.setGoalPosition(dynamixel::MAX_ANGLE + 1));
}

TEST_F(MotorTest, setGoalTorqueBoundsCheckPasses){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.setGoalTorque(100.0);

    ASSERT_FALSE(m.setGoalTorque(dynamixel::MIN_TORQUE - 1));
    ASSERT_FALSE(m.setGoalTorque(dynamixel::MAX_TORQUE + 1));
}

TEST_F(MotorTest, CanLockEEPROM){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.lockEEPROM();
}

TEST_F(MotorTest, CanSetPunch){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.setPunch(10.0);

    ASSERT_FALSE(m.setPunch(dynamixel::MIN_PUNCH - 1));
    ASSERT_FALSE(m.setPunch(dynamixel::MAX_PUNCH + 1));
}

TEST_F(MotorTest, CanGetGoalPosition){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    float angle = 0;
    m.getPosition(angle);
}

TEST_F(MotorTest, CanGetLoad){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    float load = 0;
    m.getLoad(load);
}

TEST_F(MotorTest, CanGetVoltage){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    float voltage = 0;
    m.getVoltage(voltage);
}

TEST_F(MotorTest, CanGetTemperature){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    uint8_t temp = 0;
    m.getTemperature(temp);
}

TEST_F(MotorTest, CanCheckIfIsJointMode){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    bool isJointMode = false;
    m.isJointMode(isJointMode);
}

TEST_F(MotorTest, CanPing){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    uint8_t retrievedId;
    m.ping(retrievedId);
}

TEST_F(MotorTest, CanCheckIfIsMoving){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    bool isMoving = false;
    m.isMoving(isMoving);
}

TEST_F(MotorTest, CanEnterWheelMode){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.enterWheelMode();
}

TEST_F(MotorTest, CanEnterJointMode){
    DaisyChain chain(p);
    MockMotor m(1, &chain, ResolutionDivider::AX12A);

    m.enterJointMode();
}

TEST_F(MotorTest, ParsesKnownStatusPacketProperly){
    // TODO: look at Dynamixel manual and pick out a byte array from their
    // examples. Pass this array through the entire flow and make sure the
    // result passed to the MockUartInterface is entirely correct. Make sure
    // whatever is read back (well, "fake" read back) succeeds at checksum
    // verification. Basically, this is a regression test
    ASSERT_FALSE(true);
}

} // end anonymous namespace




/**
 * @}
 */
/* end - Motor_Test */