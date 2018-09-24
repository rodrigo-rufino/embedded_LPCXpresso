################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Project.axf

# Tool invocations
Project.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\aluno.RACK20-035525NB\Documents\LPCXpresso_8.2.2_650\workspace\CMSISv2p00_LPC17xx\Debug" -L"C:\Users\aluno.RACK20-035525NB\Documents\LPCXpresso_8.2.2_650\workspace\Lib_EaBaseBoard\Debug" -L"C:\Users\aluno.RACK20-035525NB\Documents\LPCXpresso_8.2.2_650\workspace\Lib_MCU\Debug" -Xlinker -Map="Project.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "Project_Debug.ld" -o "Project.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Project.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Project.axf"; # arm-none-eabi-objcopy -v -O binary "Project.axf" "Project.bin" ; # checksum -p LPC1769 -d "Project.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
