#include "EventHandler.h"

namespace event_handler {

/**
 * @brief Blocks on a signal set from the outside indicating that a command
 * has been given.
 * @return true if unblocked successfully and with correct notification value
 * for new input, false otherwise.
 */
bool EventHandler::waitCommand() {
    uint32_t notificationValue = 0;
    BaseType_t status = pdFALSE;

    setState(EventHandlerState::READY);
    status = xTaskNotifyWait(UINT32_MAX, UINT32_MAX, &notificationValue, portMAX_DELAY);
    setState(EventHandlerState::BUSY);

    if (status == pdTRUE && notificationValue == NOTIFY_EVENT_HANDLER_INPUT) {
        return true;
    }
    else {
        return false;
    }
}

// TODO: consider a "validate raw input" function before attempting to parse it.
//       this would include some checksum-like error checking. Also get number of bytes
//       in command (should not just rely on the number of bytes reported by communication
//       interface. For smoke test, just assume definite predefined number.

// TODO: parseCommand, serializeSystemData, serializeSensorData etc should be handled
// by the class that defines those data formats. Move those functions to where they
// belong once the command protocol is defined.

/**
 * @brief Parses a command from raw bytes format, rawCommand, into a command
 * structure, parsedCommand.
 * @return true if parsed successfully and completely, false otherwise.
 */
bool EventHandler::parseCommand(uint8_t *rawCommand, RobotGoal *parsedCommand) const {
    uint8_t robotGoalData[sizeof(RobotGoal)];
    uint8_t *robotGoalDataPtr;
    uint8_t startSeqCount;
    uint8_t totalBytesRead;

    parsedCommand->id = 0;
    robotGoalDataPtr = robotGoalData;
    startSeqCount = 0;
    totalBytesRead = 0;
    robotState.id = 0;

    for (uint8_t i = 0; i < sizeof(rawCommand); i++) { // XXX: will fail as sizeof(rawCommand) is 4.
        if (startSeqCount == 4) {
            // This control block is entered when the header sequence of
            // 0xFFFFFFFF has been received; thus we know the data we
            // receive will be in tact

            *robotGoalDataPtr = rawCommand[i];
            robotGoalDataPtr++;
            totalBytesRead++;

            if (totalBytesRead == sizeof(RobotGoal)) {
                // If, after the last couple of receive interrupts, we have
                // received sizeof(RobotGoal) bytes, then we copy the data
                // buffer into the robotGoal structure and wake the control
                // thread to distribute states to each actuator
                memcpy(parsedCommand, robotGoalData, sizeof(RobotGoal));
                robotState.id = parsedCommand->id;

                // Reset the variables to help with reception of a RobotGoal
                robotGoalDataPtr = robotGoalData;
                startSeqCount = 0;
                totalBytesRead = 0;

                continue;
            }
        } else {
            // This control block is used to verify that the data header is in tact
            if (rawCommand[i] == 0xFF) {
                startSeqCount++;
            } else {
                startSeqCount = 0;
            }
        }
    }
    return true;
}

/**
 * @brief Given a parsed command, decodes the command and its data, and sends
 * requests to the outside to carry out the command.
 * @return true if successfully dispatched, false otherwise. True does not
 * guarantee that the requests were received, only that they were sent
 * successfully.
 */
bool EventHandler::dispatchCommand(RobotGoal *parsedCommand) {
    // TODO: implement
    return true;
}

/**
 * @brief Serializes sensor data from a sensor data structure to a raw bytes
 * format.
 * @return true if successfully and completely serialized, false otherwise.
 */
bool EventHandler::serializeSensorData(void *sensorData, uint8_t *rawCommand) const {
    // TODO: implement
    return true;
}

/**
 * @brief Serializes sensor data from a sensor data structure to a raw bytes
 * format.
 * @return true if successfully and completely serialized, false otherwise.
 */
bool EventHandler::serializeSystemData(void *systemData, uint8_t *rawCommand) const {
    // TODO: implement
    return true;
}

/**
 * @brief Makes calls to the EquipmentHandler to set motors to a given
 * position.
 * @return true if successfully made calls to EquipmentHandler, false otherwise.
 */
bool EventHandler::setMotorPositions(void *motorPositionsData) const {
    // TODO: implement
    return true;
}

/**
 * @brief Blocks, polling sensorDataCache until it has been refreshed completely
 * with new data.
 * @return
 */
bool EventHandler::waitSensorDataRefresh() const {
    // TODO: implement
     return true;
}

/**
 * @brief Reads SensorDataCache in its current state for data, by deep copying to
 * the previously allocated value of parameter sensorData.
 */
bool EventHandler::getSensorData(void *sensorData) const {
    // TODO: implement
    return true;
}

/**
 * @brief Reads the system for status data, by deep copying to the previously
 * allocated value of parameter systemData.
 */
bool EventHandler::getSystemStatus(void *systemData) const {
    // TODO: implement
    return true;
}

EventHandlerState_t EventHandler::getState() const {
    return state;
}

// TODO: synchronize this
void EventHandler::setState(EventHandlerState_t stateIn) {
    state = stateIn;
}

} // end namespace event_handler
