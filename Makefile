
CXX = g++

CXXFLAGS = -std=c++17 -g -Wall -Wextra -pedantic -I src 

TARGET = main

SRCS = main.cpp $(wildcard src/*.cpp)

OBJS = $(SRCS:.cpp=.o)

TARGET = shell

$(TARGET): $(OBJS)
	echo "linking obj file: $(OBJS)"
	$(CXX) $(OBJS) -o $(TARGET)

# $< is the first dependency (the .cpp file)
# $@ is the target name (the .o file)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)


