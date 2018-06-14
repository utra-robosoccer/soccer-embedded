#include <serial.h>
#include <string.h>

void send_state(RobotState* robotstate) {
	HAL_UART_Transmit(&huart1, (uint8_t *) robotstate, sizeof(RobotState), 10);
	HAL_UART_Transmit(&huart2, (uint8_t *) robotstate, sizeof(RobotState), 10);
}

RobotGoal receive_state() {
	RobotGoal r;

	return r;
}

