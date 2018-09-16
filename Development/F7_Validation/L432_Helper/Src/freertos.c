/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "usart.h"

typedef struct{
    uint8_t id;
    uint16_t pos;
}Data_t;
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId RXHandle;
uint32_t RXBuffer[ 512 ];
osStaticThreadDef_t RXControlBlock;
osThreadId TXHandle;
uint32_t TXBuffer[ 512 ];
osStaticThreadDef_t TXControlBlock;
osMessageQId toBeSentQHandle;
uint8_t toBeSentQBuffer[ 1 * sizeof( Data_t ) ];
osStaticMessageQDef_t toBeSentQControlBlock;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
extern void StartRX(void const * argument);
extern void StartTX(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of RX */
  osThreadStaticDef(RX, StartRX, osPriorityRealtime, 0, 512, RXBuffer, &RXControlBlock);
  RXHandle = osThreadCreate(osThread(RX), NULL);

  /* definition and creation of TX */
  osThreadStaticDef(TX, StartTX, osPriorityHigh, 0, 512, TXBuffer, &TXControlBlock);
  TXHandle = osThreadCreate(osThread(TX), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the queue(s) */
  /* definition and creation of toBeSentQ */
  osMessageQStaticDef(toBeSentQ, 1, Data_t, toBeSentQBuffer, &toBeSentQControlBlock);
  toBeSentQHandle = osMessageCreate(osMessageQ(toBeSentQ), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */
#define NOTIFIED_FROM_TX_ISR 0x80
#define NOTIFIED_FROM_RX_ISR 0x60
#define NOTIFIED_FROM_TASK 0x40

#define INST_WRITE_DATA 0x03
#define INST_READ_DATA 0x02

#define REG_GOAL_POSITION 0x1E
#define REG_CURRENT_POSITION 0x24


static inline BaseType_t waitUntilNotifiedOrTimeout(
    uint32_t notificationVal,
    TickType_t timeout
)
{
    uint32_t notification;
    BaseType_t status;

    // Wait until notified from ISR. Clear no bits on entry in case the notification
    // came while a higher priority task was executing.
    do{
        status = xTaskNotifyWait(0, notificationVal, &notification, pdMS_TO_TICKS(timeout));
    }while((notification & notificationVal) != notificationVal);

    return status;
}


static inline uint8_t Dynamixel_ComputeChecksum(uint8_t *arr, int length){
    uint8_t accumulate = 0;

    /* Loop through the array starting from the 2nd element of the array and
     * finishing before the last since the last is where the checksum will
     * be stored */
    for(uint8_t i = 2; i < length - 1; i++){
        accumulate += arr[i];
    }

    return (~accumulate) & 0xFF; // Lower 8 bits of the logical NOT of the sum
}


void StartRX(void const * argument){
    BaseType_t status;
    uint8_t buf[9] = {0};
    Data_t data;

    for(;;){
        HAL_UART_Receive_IT(&huart1, buf, 4);

        status = waitUntilNotifiedOrTimeout(NOTIFIED_FROM_RX_ISR, 30);

        if((status == pdTRUE) && ((buf[3] == 5) || (buf[3] == 4))){
            data.id = buf[2]; // store the id

            // Here we check the byte which indicates the length
            // of the data in the packet.
            // Assume that 5 is for set goal position and 4 is for
            // read position
            HAL_UART_Receive_IT(&huart1, &buf[4], buf[3]);
            status = waitUntilNotifiedOrTimeout(NOTIFIED_FROM_RX_ISR, 2);

            if((buf[4] == INST_WRITE_DATA) && (buf[5] == REG_GOAL_POSITION)){
                data.pos = buf[6] | (buf[7] << 8); // store the goal position
            }
            else if((buf[4] == INST_READ_DATA) && (buf[5] == REG_CURRENT_POSITION)){
                xQueueSend(toBeSentQHandle, &data, 0);
            }
        }

        if(status != pdTRUE){
            HAL_UART_AbortReceive(&huart1);
        }
    }
}


void StartTX(void const * argument){
    BaseType_t status;
    uint8_t buf[8] = {0xFF, 0xFF, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00};
    Data_t data;
    uint8_t err = 0; // add some variance to the data

    for(;;){
        while(xQueueReceive(toBeSentQHandle, &data, portMAX_DELAY) != pdTRUE);

        ++err;
        if(err > 64){
            err = 0;
        }

        buf[2] = data.id;
        buf[5] = (data.pos & 0xFF) + err; // low byte
        buf[6] = (data.pos >> 8) & 0xFF; // high byte
        buf[7] = Dynamixel_ComputeChecksum(buf, sizeof(buf));

        HAL_UART_Transmit_DMA(&huart1, buf, 8);

        status = waitUntilNotifiedOrTimeout(NOTIFIED_FROM_TX_ISR, 2);

        if(status != pdTRUE){
            HAL_UART_AbortTransmit(&huart1);
        }
    }
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(huart == &huart1){
        xTaskNotifyFromISR(
            StartTX,
            NOTIFIED_FROM_TX_ISR,
            eSetBits,
            &xHigherPriorityTaskWoken
        );
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(huart == &huart1){
        xTaskNotifyFromISR(
            StartRX,
            NOTIFIED_FROM_RX_ISR,
            eSetBits,
            &xHigherPriorityTaskWoken
        );
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/