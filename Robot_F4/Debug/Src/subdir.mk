################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/dma.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_hal_timebase_TIM.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/usart.c 

CPP_SRCS += \
../Src/main.cpp 

OBJS += \
./Src/dma.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_hal_timebase_TIM.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/usart.o 

C_DEPS += \
./Src/dma.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_hal_timebase_TIM.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/usart.d 

CPP_DEPS += \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -fprofile-arcs -ftest-coverage -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F446xx -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Common/include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Drivers/CMSIS/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/%.o: ../Src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -fprofile-arcs -ftest-coverage -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F446xx -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Drivers/CMSIS/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Robot_F4/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Common/include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


