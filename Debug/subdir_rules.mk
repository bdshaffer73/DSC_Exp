################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
DSP2833x_ADC_cal.obj: ../DSP2833x_ADC_cal.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/common/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/FPUfastRTS/c28/include" -g --define=_DEBUG --define=LARGE_MODEL --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="DSP2833x_ADC_cal.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_Adc.obj: ../DSP2833x_Adc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/common/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/FPUfastRTS/c28/include" -g --define=_DEBUG --define=LARGE_MODEL --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="DSP2833x_Adc.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_CodeStartBranch.obj: ../DSP2833x_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/common/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/FPUfastRTS/c28/include" -g --define=_DEBUG --define=LARGE_MODEL --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="DSP2833x_CodeStartBranch.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_CpuTimers.obj: ../DSP2833x_CpuTimers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/common/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/FPUfastRTS/c28/include" -g --define=_DEBUG --define=LARGE_MODEL --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="DSP2833x_CpuTimers.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_DefaultIsr.obj: ../DSP2833x_DefaultIsr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/common/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/FPUfastRTS/c28/include" -g --define=_DEBUG --define=LARGE_MODEL --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="DSP2833x_DefaultIsr.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_EPwm.obj: ../DSP2833x_EPwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/common/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/FPUfastRTS/c28/include" -g --define=_DEBUG --define=LARGE_MODEL --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="DSP2833x_EPwm.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_GlobalVariableDefs.obj: ../DSP2833x_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/common/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/FPUfastRTS/c28/include" -g --define=_DEBUG --define=LARGE_MODEL --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="DSP2833x_GlobalVariableDefs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_PieCtrl.obj: ../DSP2833x_PieCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/common/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/FPUfastRTS/c28/include" -g --define=_DEBUG --define=LARGE_MODEL --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="DSP2833x_PieCtrl.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_PieVect.obj: ../DSP2833x_PieVect.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/common/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/FPUfastRTS/c28/include" -g --define=_DEBUG --define=LARGE_MODEL --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="DSP2833x_PieVect.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_SysCtrl.obj: ../DSP2833x_SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/common/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/FPUfastRTS/c28/include" -g --define=_DEBUG --define=LARGE_MODEL --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="DSP2833x_SysCtrl.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_usDelay.obj: ../DSP2833x_usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/common/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/FPUfastRTS/c28/include" -g --define=_DEBUG --define=LARGE_MODEL --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="DSP2833x_usDelay.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Example_2833xAdcSeqModeTest.obj: ../Example_2833xAdcSeqModeTest.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2833x/common/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/libraries/math/FPUfastRTS/c28/include" -g --define=_DEBUG --define=LARGE_MODEL --quiet --verbose_diagnostics --diag_warning=225 --diag_suppress=10063 --issue_remarks --preproc_with_compile --preproc_dependency="Example_2833xAdcSeqModeTest.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


