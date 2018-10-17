################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/PressureSensor.c \
../Src/adc.c \
../Src/dma.c \
../Src/gpio.c \
../Src/main.c \
../Src/stm32l4xx_hal_msp.c \
../Src/stm32l4xx_it.c \
../Src/system_stm32l4xx.c \
../Src/usart.c 

OBJS += \
./Src/PressureSensor.o \
./Src/adc.o \
./Src/dma.o \
./Src/gpio.o \
./Src/main.o \
./Src/stm32l4xx_hal_msp.o \
./Src/stm32l4xx_it.o \
./Src/system_stm32l4xx.o \
./Src/usart.o 

C_DEPS += \
./Src/PressureSensor.d \
./Src/adc.d \
./Src/dma.d \
./Src/gpio.d \
./Src/main.d \
./Src/stm32l4xx_hal_msp.d \
./Src/stm32l4xx_it.d \
./Src/system_stm32l4xx.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L432xx -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/Foot_Pressure_Sensor_Standalone/MCU-Side/Foot_Pressure_Sensor_v1/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/Foot_Pressure_Sensor_Standalone/MCU-Side/Foot_Pressure_Sensor_v1/Drivers/STM32L4xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/Foot_Pressure_Sensor_Standalone/MCU-Side/Foot_Pressure_Sensor_v1/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/Foot_Pressure_Sensor_Standalone/MCU-Side/Foot_Pressure_Sensor_v1/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/Foot_Pressure_Sensor_Standalone/MCU-Side/Foot_Pressure_Sensor_v1/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


