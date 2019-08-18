

INCLUDES   := -I/usr/local/include -I.. -I. -I../../../include
LIBS       := -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lrt -lpthread -lcrypto -lssl
CFLAGS     := -std=c++17
BUILD_PATH := ./build
OBJ_DIR    := $(BUILD_PATH)/objects
BIN_DIR    := $(BUILD_PATH)/bin
CXX        := g++
SRC_EXT    := cpp
SRC_PATH   := ..

SOURCES    := $(SRC_PATH)/wsapi.cpp $(SRC_PATH)/config.cpp
HEADERS    := $(SRC_PATH)/wsapi.hpp $(SRC_PATH)/config.hpp

OBJECTS    := $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)

all: build $(BIN_DIR)/bitstamp_multi $(BIN_DIR)/general_listener $(BIN_DIR)/config_test $(BIN_DIR)/async_ssl_bitstamp_allsteps

build:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.cpp $(HEADERS)
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ -c $<

.PHONY: all build clean debug release o3

$(BIN_DIR)/bitstamp_multi : bitstamp_multi.cpp $(OBJECTS) $(HEADERS)
	$(CXX) $(CFLAGS) $(INCLUDES) bitstamp_multi.cpp -o $@ $(OBJECTS) $(LIBS)

$(BIN_DIR)/general_listener : general_listener.cpp $(OBJECTS) $(HEADERS)
	$(CXX) $(CFLAGS) $(INCLUDES) general_listener.cpp -o $@ $(OBJECTS) $(LIBS)

$(BIN_DIR)/config_test : config_test.cpp $(OBJECTS) $(HEADERS)
	$(CXX) $(CFLAGS) $(INCLUDES) config_test.cpp -o $@ $(OBJECTS) $(LIBS)

$(BIN_DIR)/async_ssl_bitstamp_allsteps : async_ssl_bitstamp_allsteps.cpp 
	$(CXX) $(CFLAGS) $(INCLUDES) async_ssl_bitstamp_allsteps.cpp -o $@ $(LIBS)



debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O2
release: all

o3: CFLAGS += -O3
o3: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(BIN_DIR)/*

