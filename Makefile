PIO_USER_LIBS_HOME=$(PWD)/.piolibdeps
PIO_HOME := $(HOME)/.platformio
FRAMEWORK_DIR := $(PIO_HOME)/packages/framework-arduinoavr

CXX := g++
CXXFLAGS := -g -std=gnu++11
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD := $(PWD)/build
OBJ_DIR := $(BUILD)/objects
APP_DIR := $(BUILD)/apps
TARGET := program
INCLUDE_FILES  := \
	$(dir $(wildcard src/tests/*.h)) \
	$(dir $(wildcard lib/*/*.h)) \
	$(dir $(wildcard src/*.h)) \
	$(dir $(wildcard $(PIO_USER_LIBS_HOME)/*/*.h)) \
	$(dir $(wildcard $(PIO_USER_LIBS_HOME)/*/src/*.h))
INCLUDE := $(INCLUDE_FILES:%=-I%)

# This should not be part of src for now
# As it includes main program main
# $(wildcard src/*.cpp)

SRC := \
	$(wildcard src/tests/*.cpp) \
	$(wildcard lib/*/*.cpp) \
	$(wildcard $(PIO_USER_LIBS_HOME)/*.cpp) \
	$(wildcard $(PIO_USER_LIBS_HOME)/src/*.cpp)
OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

INCLUDE += \
	-I$(FRAMEWORK_DIR)/cores/arduino/ \
	-I$(FRAMEWORK_DIR)/cores/core13/ \
	-I$(PIO_HOME)/packages/toolchain-atmelavr/avr/include

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	echo "Hello"
	echo mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	echo "Hello"
	mkdir -p $(@D)
	echo $(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*