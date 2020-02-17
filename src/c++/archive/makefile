

INCLUDES   := -I/usr/local/include -I.. -I. -I../../include
LIBS       := -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lrt -lpthread -lcrypto -lssl
CFLAGS     := -std=c++17
BUILD_PATH := ./examples/build
OBJ_DIR    := $(BUILD_PATH)/objects
BIN_DIR    := $(BUILD_PATH)/bin
CXX        := g++
SRC_EXT    := cpp

SOURCES    := wsapi.cpp config.cpp
HEADERS    := wsapi.hpp config.hpp

OBJECTS    := $(SOURCES:%.$(SRC_EXT)=$(OBJ_DIR)/%.o)

all: build $(BIN_DIR)/simple_example

build:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ -c $<

.PHONY: all build clean debug release o3

$(BIN_DIR)/simple_example : simple_example.cpp $(OBJECTS) $(HEADERS)
	$(CXX) $(CFLAGS) $(INCLUDES) simple_example.cpp -o $@ $(OBJECTS) $(LIBS)

debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O2
release: all

o3: CFLAGS += -O3
o3: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(BIN_DIR)/*

