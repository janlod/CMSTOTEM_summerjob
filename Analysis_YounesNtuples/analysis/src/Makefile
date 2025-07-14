#CXXFLAGS = -O2 -Wall -std=c++17
CXXFLAGS = -g -O0 -Wall


ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --glibs)

TARGET = exe_ana
SRCS = main.cc
OBJS = $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -g -o $@ $(ROOTLIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run
