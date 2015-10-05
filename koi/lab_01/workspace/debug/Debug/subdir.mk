################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../a.o \
../abc.o \
../abscissa.o \
../absurdum.o \
../ack.o \
../metamatic.o 

CPP_SRCS += \
../a.cpp \
../abc.cpp \
../abscissa.cpp \
../absurdum.cpp \
../ack.cpp \
../metamatic.cpp 

OBJS += \
./a.o \
./abc.o \
./abscissa.o \
./absurdum.o \
./ack.o \
./metamatic.o 

CPP_DEPS += \
./a.d \
./abc.d \
./abscissa.d \
./absurdum.d \
./ack.d \
./metamatic.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


