################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/dma.c \
../Src/freertos.c \
../Src/gpio.c \
../Src/main.c \
../Src/stm32h7xx_hal_msp.c \
../Src/stm32h7xx_hal_timebase_TIM.c \
../Src/stm32h7xx_it.c \
../Src/system_stm32h7xx.c \
../Src/usart.c 

OBJS += \
./Src/dma.o \
./Src/freertos.o \
./Src/gpio.o \
./Src/main.o \
./Src/stm32h7xx_hal_msp.o \
./Src/stm32h7xx_hal_timebase_TIM.o \
./Src/stm32h7xx_it.o \
./Src/system_stm32h7xx.o \
./Src/usart.o 

C_DEPS += \
./Src/dma.d \
./Src/freertos.d \
./Src/gpio.d \
./Src/main.d \
./Src/stm32h7xx_hal_msp.d \
./Src/stm32h7xx_hal_timebase_TIM.d \
./Src/stm32h7xx_it.d \
./Src/system_stm32h7xx.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32H743xx -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Drivers/STM32H7xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


