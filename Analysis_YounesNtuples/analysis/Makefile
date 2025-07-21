CXX = g++
#CXXFLAGS = -O2 -Wall -std=c++17
CXXFLAGS = -g -O0 -Wall

ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --glibs)

INCLUDE_DIR = include
SRC_DIR = src

SRCS = $(shell find $(SRC_DIR) -name '*.cc') main.cc
OBJS = $(SRCS:.cc=.o)

TARGET = exe_ana

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(ROOTLIBS)

# Pattern rule for all .o files
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run

