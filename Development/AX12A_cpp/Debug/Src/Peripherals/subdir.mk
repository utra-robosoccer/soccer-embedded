################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Peripherals/gpio.c \
../Src/Peripherals/i2c.c \
../Src/Peripherals/stm32h7xx_hal_msp.c \
../Src/Peripherals/stm32h7xx_it.c \
../Src/Peripherals/system_stm32h7xx.c \
../Src/Peripherals/usart.c 

OBJS += \
./Src/Peripherals/gpio.o \
./Src/Peripherals/i2c.o \
./Src/Peripherals/stm32h7xx_hal_msp.o \
./Src/Peripherals/stm32h7xx_it.o \
./Src/Peripherals/system_stm32h7xx.o \
./Src/Peripherals/usart.o 

C_DEPS += \
./Src/Peripherals/gpio.d \
./Src/Peripherals/i2c.d \
./Src/Peripherals/stm32h7xx_hal_msp.d \
./Src/Peripherals/stm32h7xx_it.d \
./Src/Peripherals/system_stm32h7xx.d \
./Src/Peripherals/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Peripherals/%.o: ../Src/Peripherals/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -DUSE_HAL_DRIVER -DSTM32H743xx '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/AX12A_cpp/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/AX12A_cpp/Drivers/STM32H7xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/AX12A_cpp/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/AX12A_cpp/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Development/AX12A_cpp/Drivers/CMSIS/Include"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


