################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/MX28/MX28.cpp 

OBJS += \
./Src/MX28/MX28.o 

CPP_DEPS += \
./Src/MX28/MX28.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MX28/%.o: ../Src/MX28/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -DUSE_HAL_DRIVER -DSTM32H743xx '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/AX12A_cpp/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/AX12A_cpp/Drivers/STM32H7xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/AX12A_cpp/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/AX12A_cpp/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/AX12A_cpp/Drivers/CMSIS/Include"  -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


