################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MPU6050/MPU6050.c \
../Drivers/MPU6050/MPUFilter.c 

OBJS += \
./Drivers/MPU6050/MPU6050.o \
./Drivers/MPU6050/MPUFilter.o 

C_DEPS += \
./Drivers/MPU6050/MPU6050.d \
./Drivers/MPU6050/MPUFilter.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MPU6050/%.o: ../Drivers/MPU6050/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L432xx -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/IMU_Digital_Filter/IMU_Digital_Filter/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/IMU_Digital_Filter/IMU_Digital_Filter/Drivers/STM32L4xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/IMU_Digital_Filter/IMU_Digital_Filter/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/IMU_Digital_Filter/IMU_Digital_Filter/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/IMU_Digital_Filter/IMU_Digital_Filter/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/IMU_Digital_Filter/IMU_Digital_Filter/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/IMU_Digital_Filter/IMU_Digital_Filter/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/IMU_Digital_Filter/IMU_Digital_Filter/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


