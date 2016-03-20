
CXX = g++
INCLUDES = 
LIBS     = -lstdc++
CXXFLAGS = $(INCLUDES) -Wall -g -std=c++14
LIBFLAGS = 
AR       = ar

.SUFFIXES: .cpp .o

# Create a list of source files.
SOURCES  = $(shell ls *.cpp)

all : Main

Main: $(SOURCES)
	$(CXX) -o Main $(CXXFLAGS) $(SOURCES) $(LIBS)
clean:
	rm -rf *.o Main