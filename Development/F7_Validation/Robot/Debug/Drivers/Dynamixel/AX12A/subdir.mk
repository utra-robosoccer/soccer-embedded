################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Dynamixel/AX12A/AX12A.c 

OBJS += \
./Drivers/Dynamixel/AX12A/AX12A.o 

C_DEPS += \
./Drivers/Dynamixel/AX12A/AX12A.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Dynamixel/AX12A/%.o: ../Drivers/Dynamixel/AX12A/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F767xx -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/F7_Validation/Robot/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


