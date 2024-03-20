# compiler and compilation options
CXX ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations -I../pacs-examples/Examples/include -I../pacs-examples/Examples/include/muparser

# executable name 
EXEC     = main
LDFLAGS ?= -L../pacs-examples/Examples/lib -Wl,-rpath=/home/lucadalessandro/pacs-examples/Examples/lib/muparser.so.2

LIBS ?= -lmuparser

# source files
SRCS = main.cpp Point.cpp Gradient_method.cpp 
OBJS = $(SRCS:.cpp=.o)

# header files
HDRS = parameters.hpp muparser_fun.hpp Point.hpp Gradient_method.hpp

# rules
all: $(EXEC)

%.o: %.cpp $(HDRS)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@
 
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

clean:
	$(RM) *.o