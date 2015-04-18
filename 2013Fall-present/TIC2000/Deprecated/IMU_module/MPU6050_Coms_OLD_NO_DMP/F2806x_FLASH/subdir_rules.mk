################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
BlinkingLED-DevInit_F2806x.obj: ../BlinkingLED-DevInit_F2806x.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/lib" --include_path="/packages/ti/xdais" --include_path="C:/ti/controlSUITE/development_kits/~SupportFiles/F2806x_headers" --include_path="C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_headers/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_common/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --diag_warning=225 --preproc_with_compile --preproc_dependency="BlinkingLED-DevInit_F2806x.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_CodeStartBranch.obj: C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_common/source/F2806x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/lib" --include_path="/packages/ti/xdais" --include_path="C:/ti/controlSUITE/development_kits/~SupportFiles/F2806x_headers" --include_path="C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_headers/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_common/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --diag_warning=225 --preproc_with_compile --preproc_dependency="F2806x_CodeStartBranch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_GlobalVariableDefs.obj: C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_headers/source/F2806x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/lib" --include_path="/packages/ti/xdais" --include_path="C:/ti/controlSUITE/development_kits/~SupportFiles/F2806x_headers" --include_path="C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_headers/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_common/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --diag_warning=225 --preproc_with_compile --preproc_dependency="F2806x_GlobalVariableDefs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

I2CFuncs.obj: ../I2CFuncs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/lib" --include_path="/packages/ti/xdais" --include_path="C:/ti/controlSUITE/development_kits/~SupportFiles/F2806x_headers" --include_path="C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_headers/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_common/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --diag_warning=225 --preproc_with_compile --preproc_dependency="I2CFuncs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MPUFuncs.obj: ../MPUFuncs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/lib" --include_path="/packages/ti/xdais" --include_path="C:/ti/controlSUITE/development_kits/~SupportFiles/F2806x_headers" --include_path="C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_headers/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_common/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --diag_warning=225 --preproc_with_compile --preproc_dependency="MPUFuncs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Programming/TI/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/lib" --include_path="/packages/ti/xdais" --include_path="C:/ti/controlSUITE/development_kits/~SupportFiles/F2806x_headers" --include_path="C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_headers/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v100/F2806x_common/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --diag_warning=225 --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


