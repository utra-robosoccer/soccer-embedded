/******************** Define to prevent recursive inclusion *******************/
#ifndef __UART_HANDLER_H
#define __UART_HANDLER_H

#ifdef stm32f4xx_hal
	#include "stm32f4xx_hal.h"
	#include "stm32f4xx_hal_conf.h"
#endif

#ifdef stm32h7xx_hal
	#include "stm32h7xx_hal.h"
	#include "stm32h7xx_hal_conf.h"
#endif

#include "../Drivers/Dynamixel/DynamixelProtocolV1.h"

#define cmdREAD			0
#define cmdWRITE		1

typedef struct {
	uint8_t 					type;
	Dynamixel_HandleTypeDef*	motorHandle;
	float 						position;
	float 						velocity;
	QueueHandle_t				qHandle;
}UARTcmd;

typedef struct {
	Dynamixel_HandleTypeDef*	motorHandle;
	float 						position;
	float 						velocity;
}UARTrx;

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#endif
