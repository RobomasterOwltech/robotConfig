# This file contains compilation instructions dependent on the development board.
# THIS IS NOT A STANDALONE MAKE FILE. 
# ==========================================
# Possible improvements:
# * Don't compile everything, only the enabled modules at stm32f1xx_hal_conf.h
# ==========================================
# Made by Jorge Pérez 4 Owltech <3


# ==============
# Proccesor info
# ==============

# ===== Device
C_DEFS +=  \
-DSTM32F100xB

# ===== CPU
CPU = -mcpu=cortex-m3

# ===== ARCH
ARCH_ARM = ARM_CM3
PROC_TYPE = STM32F1xx

# ===== FPU
## Floating Point Unit
## See more at: https://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/ARM-Options.html
FPU = -msoft-float

# ===== float-abi
FLOAT-ABI = -mfloat-abi=soft

# ===== MCU
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)


# ==============
# Code files
# ==============

# This is defined for the container
FirmwarePath = /opt/STM32CubeF1

# Check if variable has defined the USE_HAL_DRIVER flag
HAL_Eval = $(shell echo $(C_DEFS) | grep -c USE_HAL_DRIVER)

# ===== ===== C Includes
C_INCLUDES +=  \
-IrobotConfig/inc

# Add HAL 
ifeq ($(HAL_Eval), 1)
	C_INCLUDES += \
	-I$(FirmwarePath)/Drivers/$(PROC_TYPE)_HAL_Driver/Inc \
	-I$(FirmwarePath)/Drivers/$(PROC_TYPE)_HAL_Driver/Inc/Legacy \
	-I$(FirmwarePath)/Drivers/CMSIS/Device/ST/$(PROC_TYPE)/Include \
	-I$(FirmwarePath)/Drivers/CMSIS/Include
endif

# ===== ===== C Sources
C_SOURCES += \
$(shell find robotConfig/src/*.c)

# Add HAL 
ifeq ($(HAL_Eval), 1)
	C_SOURCES +=$(shell find $(FirmwarePath)/Drivers/$(PROC_TYPE)_HAL_Driver/Src/*.c ! -name *template.c)
endif

# ===== ASM Sources
ASM_SOURCES += \
robotConfig/Startup/startup_stm32f100rbtx.s

# ===== link script
LDSCRIPT += \
robotConfig/Startup/STM32F100RBTX_FLASH.ld

showConfig: 
	$(info ===== ===== ===== ===== ===== ===== =====)
	$(info This project works with the STM32VLDISCOVERY)
	$(info Based on your current flags, the config is:)
	$(info CPU : $(CPU))
	$(info ARCH : $(ARCH))
	$(info FPU : $(FPU))
	$(info FLOAT-ABI : $(FLOAT-ABI))
	$(info Leading to:)
	$(info MCU : $(MCU))
	$(info ===== ===== ===== ===== ===== ===== =====)
	$(info Source files:)
	$(info  $(C_SOURCES))
	$(info ===== =====)
	$(info Include paths:)
	$(info  $(C_INCLUDES))
	$(info ===== =====)
	$(info ASM files:)
	$(info  $(ASM_SOURCES))
	$(info ===== =====)
	$(info Linker files:)
	$(info  $(LDSCRIPT))
	$(info HAL EVAL $(HAL_Eval))
