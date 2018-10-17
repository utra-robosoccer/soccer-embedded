################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/UART_Handler.c \
../Src/dma.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/stm32f7xx_hal_msp.c \
../Src/stm32f7xx_hal_timebase_TIM.c \
../Src/stm32f7xx_it.c \
../Src/system_stm32f7xx.c \
../Src/usart.c 

CPP_SRCS += \
../Src/freertos.cpp \
../Src/main.cpp 

OBJS += \
./Src/UART_Handler.o \
./Src/dma.o \
./Src/freertos.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/stm32f7xx_hal_msp.o \
./Src/stm32f7xx_hal_timebase_TIM.o \
./Src/stm32f7xx_it.o \
./Src/system_stm32f7xx.o \
./Src/usart.o 

C_DEPS += \
./Src/UART_Handler.d \
./Src/dma.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/stm32f7xx_hal_msp.d \
./Src/stm32f7xx_hal_timebase_TIM.d \
./Src/stm32f7xx_it.d \
./Src/system_stm32f7xx.d \
./Src/usart.d 

CPP_DEPS += \
./Src/freertos.d \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F767xx -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/%.o: ../Src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -ftest-coverage -fprofile-arcs -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F767xx -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


