

INCLUDES   := -I/usr/local/include -I.. -I. -I../../../include
LIBS       := -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lrt -lpthread -lcrypto -lssl
CFLAGS     := -std=c++17
BUILD_PATH := ./build
OBJ_DIR    := $(BUILD_PATH)/objects
BIN_DIR    := $(BUILD_PATH)/bin
CXX        := g++
SRC_EXT    := cpp

SOURCES    := wsapi.cpp
HEADERS    := wsapi.hpp

OBJECTS    := $(SOURCES:%.$(SRC_EXT)=$(OBJ_DIR)/%.o)

first: build $(BIN_DIR)/bitstamp

build:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ -c $<

.PHONY: all build clean debug release o3

$(BIN_DIR)/bitstamp : bitstamp.cpp $(OBJECTS) $(HEADERS)
	$(CXX) $(CFLAGS) $(INCLUDES) bitstamp.cpp -o $@ $(OBJECTS) $(LIBS)

$(BIN_DIR)/simple_example : simple_example.cpp $(OBJECTS) $(HEADERS)
	$(CXX) $(CFLAGS) $(INCLUDES) simple_example.cpp -o $@ $(OBJECTS) $(LIBS)

$(BIN_DIR)/async_ssl_bitstamp_allsteps : async_ssl_bitstamp_allsteps.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) async_ssl_bitstamp_allsteps.cpp -o $@ $(LIBS)

all: build $(BIN_DIR)/bitstamp $(BIN_DIR)/simple_example $(BIN_DIR)/async_ssl_bitstamp_allsteps

debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O2
release: all

o3: CFLAGS += -O3
o3: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(BIN_DIR)/*

