CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -Iinclude 

SHELL_EXEC = myshell
SHELL_SRC = main.cpp src/mkdir.cpp src/cd.cpp src/rm.cpp
SHELL_OBJS = $(SHELL_SRC:.cpp=.o)

# Find all .cpp files in src/
ALL_SRC = $(wildcard src/*.cpp)

BUILTIN_SRCS = src/mkdir.cpp src/cd.cpp src/rm.cpp src/grep.cpp

PIPE_SRCS = $(filter-out $(BUILTIN_SRCS), $(ALL_SRC))

# Define the names of the pipe executables (e.g., src/find, src/grep)
PIPE_EXECS = $(PIPE_SRCS:.cpp=)

all: $(SHELL_EXEC) $(PIPE_EXECS)

# Link main shell
$(SHELL_EXEC): $(SHELL_OBJS)
	$(CXX) $(CXXFLAGS) -o $(SHELL_EXEC) $(SHELL_OBJS)

# Compile .cpp to .o (for the shell built-ins and main)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target: src/find, Prerequisite: src/find.cpp
src/%: src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean
clean:
	rm -f $(SHELL_EXEC) $(PIPE_EXECS) $(SHELL_OBJS)
	rm -rf src/*.dSYM

.PHONY: all clean