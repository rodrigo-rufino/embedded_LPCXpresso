################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc17.c \
../src/easyweb.c \
../src/ethmac.c \
../src/ew_systick.c \
../src/tcpip.c 

OBJS += \
./src/cr_startup_lpc17.o \
./src/easyweb.o \
./src/ethmac.o \
./src/ew_systick.o \
./src/tcpip.o 

C_DEPS += \
./src/cr_startup_lpc17.d \
./src/easyweb.d \
./src/ethmac.d \
./src/ew_systick.d \
./src/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"C:\Users\rodri\Documents\LPCXpresso_8.2.2_650\embedded_LPCXpresso\workspace_projeto\CMSISv2p00_LPC17xx\inc" -I"C:\Users\rodri\Documents\LPCXpresso_8.2.2_650\embedded_LPCXpresso\workspace_projeto\Lib_EaBaseBoard\inc" -I"C:\Users\rodri\Documents\LPCXpresso_8.2.2_650\embedded_LPCXpresso\workspace_projeto\Lib_MCU\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


