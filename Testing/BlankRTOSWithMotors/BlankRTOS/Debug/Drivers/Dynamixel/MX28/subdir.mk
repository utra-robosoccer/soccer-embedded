################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Dynamixel/MX28/MX28.c 

OBJS += \
./Drivers/Dynamixel/MX28/MX28.o 

C_DEPS += \
./Drivers/Dynamixel/MX28/MX28.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Dynamixel/MX28/%.o: ../Drivers/Dynamixel/MX28/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F446xx -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/BlankRTOSWithMotors/BlankRTOS/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/BlankRTOSWithMotors/BlankRTOS/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/BlankRTOSWithMotors/BlankRTOS/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/BlankRTOSWithMotors/BlankRTOS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/BlankRTOSWithMotors/BlankRTOS/Drivers/CMSIS/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/BlankRTOSWithMotors/BlankRTOS/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/BlankRTOSWithMotors/BlankRTOS/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/BlankRTOSWithMotors/BlankRTOS/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

