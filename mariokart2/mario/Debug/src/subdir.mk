################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cam_ctrl.c \
../src/main.c \
../src/platform.c \
../src/pmodACL.c \
../src/pmodGYRO.c \
../src/vmodcam_cfg.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/cam_ctrl.o \
./src/main.o \
./src/platform.o \
./src/pmodACL.o \
./src/pmodGYRO.o \
./src/vmodcam_cfg.o 

C_DEPS += \
./src/cam_ctrl.d \
./src/main.d \
./src/platform.d \
./src/pmodACL.d \
./src/pmodGYRO.d \
./src/vmodcam_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../mario_bsp/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.b -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


