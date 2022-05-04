#****************************************************************************
# Makefile
# openacousticdevices.info
# November 2020
#****************************************************************************

# Set the toolpath parameter to the location of the GNU Arm Embedded Toolchain

TOOLCHAIN_PATH = /Users/anthonyluo/Desktop/NatGeoResearch

TOOLCHAIN_VERSION = gcc-arm-none-eabi-10.3-2021.10

# Determine the path to the toolchain binary

TOOLPATH = $(TOOLCHAIN_PATH)/$(TOOLCHAIN_VERSION)/bin/

# Edge Impulse Header files 
EI_INC = ../ei_library ../ei_library/edge-impulse-sdk ../ei_library/edge-impulse-sdk/classifier ../ei_library/edge-impulse-sdk/third_party ../ei_library/edge-impulse-sdk/third_party/flatbuffers/include ../ei_library/edge-impulse-sdk/third_party/ruy ../ei_library/edge-impulse-sdk/CMSIS/NN/Include ../ei_library/edge-impulse-sdk/CMSIS/DSP/Include ../ei_library/edge-impulse-sdk/CMSIS/Core/Include ../ei_library/edge-impulse-sdk/DSP/PrivateInclude ../ei_library/edge-impulse-sdk/third_party/gemmlowp ../ei_library/edge-impulse-sdk/porting_audiomoth ../ei_library/tflite-model

# Edge Impulse and DSP Source Files
EI_SRCS = ../DSP_Lib/Source/BasicMathFunctions ../DSP_Lib/Source/CommonTables ../DSP_Lib/Source/ComplexMathFunctions ../DSP_Lib/Source/ControllerFunctions ../DSP_Lib/Source/FastMathFunctions ../DSP_Lib/Source/FilteringFunctions ../DSP_Lib/Source/MatrixFunctions ../DSP_Lib/Source/StatisticsFunctions ../DSP_Lib/Source/SupportFunctions ../DSP_Lib/Source/TransformFunctions ../ei_library/edge-impulse-sdk/CMSIS/NN/Source/ActivationFunctions ../ei_library/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions ../ei_library/edge-impulse-sdk/CMSIS/NN/Source/ConcatenationFunctions ../ei_library/edge-impulse-sdk/CMSIS/NN/Source/ConvolutionFunctions ../ei_library/edge-impulse-sdk/CMSIS/NN/Source/FullyConnectedFunctions ../ei_library/edge-impulse-sdk/CMSIS/NN/Source/NNSupportFunctions ../ei_library/edge-impulse-sdk/CMSIS/NN/Source/PoolingFunctions ../ei_library/edge-impulse-sdk/CMSIS/NN/Source/ReshapeFunctions ../ei_library/edge-impulse-sdk/CMSIS/NN/Source/SoftmaxFunctions ../ei_library/edge-impulse-sdk/dsp ../ei_library/edge-impulse-sdk/dsp/dct ../ei_library/edge-impulse-sdk/dsp/kissfft ../ei_library/edge-impulse-sdk/porting_audiomoth ../ei_library/edge-impulse-sdk/tensorflow/lite/c ../ei_library/edge-impulse-sdk/tensorflow/lite/core/api ../ei_library/edge-impulse-sdk/tensorflow/lite/kernels ../ei_library/edge-impulse-sdk/tensorflow/lite/kernels/internal ../ei_library/edge-impulse-sdk/tensorflow/lite/micro ../ei_library/edge-impulse-sdk/tensorflow/lite/micro/kernels ../ei_library/edge-impulse-sdk/tensorflow/lite/micro/memory_planner ../ei_library/edge-impulse-sdk/tensorflow/lite/micro/testing ../ei_library/source ../ei_library/tflite-model

# Source files for this project (C and C++)
SRC = ../device/src ../emlib/src ../emusb/src ../drivers/src ../fatfs/src ../gps/src ../src ../cmsis $(EI_SRCS)

# Header files for this project (C and C++)
INC = ../cmsis ../device/inc ../emlib/inc ../emusb/inc ../drivers/inc ../fatfs/inc ../gps/inc ../inc $(EI_INC)

# Set the name of the output files
FILENAME = audiomoth_ei

# This is the location of the resulting object files
OBJPATH = ./objects/

# Set the target EFM32WG to that used in AudioMoth
TARGET = EFM32WG380F256

#Optimization Level 
OPTLEVEL = -O3

# The following code generates the list of objects and the search path of source and header files

VPATH = $(SRC)

IFLAGS = $(foreach d, $(INC), -I$d)

_CPPSRC = $(notdir $(foreach d, $(SRC), $(wildcard $d/*.cpp)))
_CPPSRC2 = $(notdir $(foreach d, $(SRC), $(wildcard $d/*.cc)))
_CSRC = $(notdir $(foreach d, $(SRC), $(wildcard $d/*.c)))
_SSRC = $(notdir $(foreach d, $(SRC), $(wildcard $d/*.s)))
_SSRC2 = $(notdir $(foreach d, $(SRC), $(wildcard $d/*.S)))

_OBJ = $(_CSRC:.c=.o) $(_CPPSRC:.cpp=.o) $(_CPPSRC2:.cc=.o) $(_SSRC:.s=.o) $(_SSRC2:.S=.o)

OBJ = $(sort $(foreach d, $(_OBJ), $(OBJPATH)$d))

DEP = $(OBJ:.o=.d)

# These are the compilation settings

CC = $(TOOLPATH)arm-none-eabi-gcc

CXX = $(TOOLPATH)arm-none-eabi-g++

CSIZE = $(TOOLPATH)arm-none-eabi-size

COBJCOPY = $(TOOLPATH)arm-none-eabi-objcopy

COBJDUMP = $(TOOLPATH)arm-none-eabi-objdump

CFLAGS = -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb -fmessage-length=0 -ffunction-sections -fdata-sections -Wall '-DARM_MATH_CM4=1' '-D$(TARGET)=1' '-D__FPU_PRESENT=1' '-D__TARGET_CPU_CORTEX_M4=1'

DFLAGS = -MMD

# Finally the build rules

$(OBJPATH)%.o: %.cpp
	@mkdir -p $(OBJPATH)
	@echo 'Building C++' $@
	@$(CXX) $(CFLAGS) $(DFLAGS) $(OPTLEVEL) -ffunction-sections -fdata-sections -fpermissive -std=gnu++0x -c -o "$@" "$<" $(IFLAGS)

$(OBJPATH)%.o: %.cc
	@mkdir -p $(OBJPATH)
	@echo 'Building C++' $@
	@$(CXX) $(CFLAGS) $(DFLAGS) $(OPTLEVEL) -ffunction-sections -fdata-sections -fpermissive -std=gnu++0x -c -o "$@" "$<" $(IFLAGS)

$(OBJPATH)%.o: %.c
	@mkdir -p $(OBJPATH)
	@echo 'Building C' $@
	@$(CC) $(CFLAGS) $(DFLAGS) $(OPTLEVEL) -ffunction-sections -fdata-sections -std=c99 -c -o "$@" "$<" $(IFLAGS)

$(OBJPATH)%.o: %.s
	@mkdir -p $(OBJPATH)
	@echo 'Building Assembly' $@
	@$(CC) $(CFLAGS) $(DFLAGS) -x assembler-with-cpp -c -o "$@" "$<" $(IFLAGS)

$(FILENAME).bin: $(OBJ)
	@echo 'Building' $(FILENAME).axf
	@$(CXX) -mcpu=cortex-m4 -mthumb -T "audiomoth.ld" --specs=nosys.specs -Xlinker --gc-sections -Xlinker -Map="$(FILENAME).map" -mfpu=fpv4-sp-d16 -mfloat-abi=hard --specs=nano.specs -o $(FILENAME).axf $(OBJ) -lm -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Building' $(FILENAME).lst
	@$(COBJDUMP) -d -t -S "$(FILENAME).axf" > "$(FILENAME).lst" 
	@echo 'Building' $(FILENAME).hex
	@$(COBJCOPY) -O ihex "$(FILENAME).axf" "$(FILENAME).hex"
	@echo 'Building' $(FILENAME).bin
	@$(COBJCOPY) -O binary "$(FILENAME).axf" "$(FILENAME).bin"
	@$(CSIZE) -A "$(FILENAME).axf"

-include $(DEP)

.PHONY: clean
clean:
	rm -f $(OBJPATH)*.o
	rm -f $(OBJPATH)*.d
	rm -f $(FILENAME).axf
	rm -f $(FILENAME).lst
	rm -f $(FILENAME).bin
	rm -f $(FILENAME).hex
	rm -f $(FILENAME).map
