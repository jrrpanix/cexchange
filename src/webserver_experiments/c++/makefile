INCLUDES  := -I/usr/local/include
CFLAGS    := -std=c++17
LIBS      := -L/usr/local/lib -l boost_regex -l boost_filesystem -l boost_system
BUILD_DIR := ./build
CXX       := g++

all: build $(BUILD_DIR)/boost_examples

.PHONY: all build boost_examples

build:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/boost_examples: boost_examples.cpp
	@echo $(BUILD_DIR)
	$(CXX) $(CFLAGS) boost_examples.cpp  -o$@ $(LIBS)


