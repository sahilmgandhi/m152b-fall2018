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
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
peripheral_tutorial.elf.size \

ELFCHECK += \
peripheral_tutorial.elf.elfcheck \


# All Target
all: peripheral_tutorial.elf secondary-outputs

# Tool invocations
peripheral_tutorial.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MicroBlaze gcc linker'
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L../../peripheral_tutorial_bsp/microblaze_0/lib -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.b -mno-xl-soft-mul -Wl,--no-relax -Wl,--gc-sections -o "peripheral_tutorial.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

peripheral_tutorial.elf.size: peripheral_tutorial.elf
	@echo 'Invoking: MicroBlaze Print Size'
	mb-size peripheral_tutorial.elf  |tee "peripheral_tutorial.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

peripheral_tutorial.elf.elfcheck: peripheral_tutorial.elf
	@echo 'Invoking: Xilinx ELF Check'
	elfcheck peripheral_tutorial.elf -hw ../../m152b_fall2018_hw_platform/system.xml -pe microblaze_0  |tee "peripheral_tutorial.elf.elfcheck"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) peripheral_tutorial.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
