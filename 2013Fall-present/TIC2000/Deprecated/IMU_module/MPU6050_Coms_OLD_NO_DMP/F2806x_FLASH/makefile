################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_headers/cmd/F2806x_Headers_nonBIOS.cmd" \
"./BlinkingLED-DevInit_F2806x.obj" \
"./F2806x_CodeStartBranch.obj" \
"./F2806x_GlobalVariableDefs.obj" \
"./I2CFuncs.obj" \
"./MPUFuncs.obj" \
"./main.obj" \
"../F28069.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
BlinkingLED.out \

EXE_OUTPUTS__QUOTED += \
"BlinkingLED.out" \


# All Target
all: BlinkingLED.out

# Tool invocations
BlinkingLED.out: $(OBJS) $(CMD_SRCS) $(CMD_UPPER_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --diag_warning=225 -z -m"BlinkingLED.map" --heap_size=0x400 --stack_size=0x380 --warn_sections -i"C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/lib" -i"C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/include" -i"C:/Programming/SJ/2013Fall-present/TIC2000/Depricated/IMU_module/MPU6050_Coms_OLD_NO_DMP" --reread_libs --xml_link_info="BlinkingLED_linkInfo.xml" --rom_model -o "BlinkingLED.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "BlinkingLED-DevInit_F2806x.pp" "F2806x_GlobalVariableDefs.pp" "I2CFuncs.pp" "MPUFuncs.pp" "main.pp" 
	-$(RM) "BlinkingLED-DevInit_F2806x.obj" "F2806x_CodeStartBranch.obj" "F2806x_GlobalVariableDefs.obj" "I2CFuncs.obj" "MPUFuncs.obj" "main.obj" 
	-$(RM) "F2806x_CodeStartBranch.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

