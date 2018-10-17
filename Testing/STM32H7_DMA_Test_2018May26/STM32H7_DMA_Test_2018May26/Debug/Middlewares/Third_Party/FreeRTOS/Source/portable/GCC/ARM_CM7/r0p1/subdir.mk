################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32H743xx -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Drivers/STM32H7xx_HAL_Driver/Inc" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Users/Tyler/Documents/STM/embedded/soccer-embedded/Testing/STM32H7_DMA_Test_2018May26/STM32H7_DMA_Test_2018May26/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


