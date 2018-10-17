################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/main.c \
../Src/serial.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/usart.c 

OBJS += \
./Src/gpio.o \
./Src/main.o \
./Src/serial.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/usart.o 

C_DEPS += \
./Src/gpio.d \
./Src/main.d \
./Src/serial.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F446xx '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/Blank/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/Blank/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/Blank/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/Blank/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/Blank/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


