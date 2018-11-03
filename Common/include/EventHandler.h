#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "PcInterface.h"
#include "RobotGoal.h"

#define NOTIFY_EVENT_HANDLER_INPUT 0x7272

// Central event handler, to respond to rx events, tell equipment what to do,
//exchange data with system components, and transmit to tx.
//
// Typical use cycle looks like
// 1. receive bytes from pc interface
// 2. parse the command from char array into a data structure
// 3. pass the command to equipment handler
// 4. read sensor data cache (or block on sensor data update signal)
// 5. serialize the read sensor data
// 6. transmit the sensor data to the pc

namespace event_handler {

// Can make these more specific later, but keep it simple for now
typedef enum class EventHandlerState {
    READY,
    BUSY,
    WAITING
} EventHandlerState_t;

typedef enum class EventCommandType {
    GET_SENSOR_DATA,
    SET_MOTOR_POSITIONS,
    SET_AND_GET,
    GET_STATUS,
    GET_FORCED_SENSOR_DATA
} EventCommandType_t;

struct EventCommand_t {
    EventCommandType_t commandType;
};

// TODO: move out into its own file once ready
class EquipmentHandler {
public:

private:

};


// TODO: use proper types not void*
// TODO: rethink parameters and returns for all these functions
class EventHandler {
public:
    bool waitCommand();

    bool parseCommand(uint8_t *rawCommand, RobotGoal *parsedCommand) const;

    bool dispatchCommand(RobotGoal *parsedCommand);

    bool serializeSystemData(void *systemData, uint8_t *rawCommand) const;

    bool serializeSensorData(void *sensorData, uint8_t *rawCommand) const;

    EventHandlerState_t getState() const;
private:
    bool setMotorPositions(void *motorPositionsData) const;

    bool waitSensorDataRefresh() const;

    bool getSensorData(void *sensorData) const;

    bool getSystemStatus(void *systemData) const;

    void setState(EventHandlerState_t stateIn);

    EquipmentHandler equipmentHandler;

    const pc_interface::PcInterface *pcInterface;

    const void *sensorDataCache = nullptr;

    EventHandlerState_t state = EventHandlerState::WAITING;
};

} // end namespace event_handler

#endif
