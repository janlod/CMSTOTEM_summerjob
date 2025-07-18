#CXXFLAGS = -O2 -Wall -std=c++17
CXXFLAGS = -g -O0 -Wall


ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --glibs)

# Include directory for your headers
INCLUDE_DIR = include

SRC_DIR = src
SRCS = $(shell find $(SRC_DIR) -name '*.cc') main.cc
OBJS = $(SRCS:.cc=.o)

TARGET = exe_ana

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -g -o $@ $(ROOTLIBS)

# Rule to compile main.cc (in current dir)
main.o: main.cc
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Rule to compile .cc files inside src/
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run
