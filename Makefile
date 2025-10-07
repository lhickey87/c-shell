CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# --- Shell (Built-in) Configuration ---
SHELL_EXEC = myshell
SHELL_SRC = main.cpp src/mkdir.cpp src/cd.cpp src/rm.cpp
SHELL_OBJS = $(SHELL_SRC:.cpp=.o)

# --- Pipe Executable Configuration ---
# Find all .cpp files in src/
ALL_SRC = $(wildcard src/*.cpp)

# Define which src files are built-ins (objects linked into the main shell)
BUILTIN_SRCS = src/mkdir.cpp src/cd.cpp src/rm.cpp

# Define which src files are external pipe executables
PIPE_SRCS = $(filter-out $(BUILTIN_SRCS), $(ALL_SRC))

# Define the names of the pipe executables (e.g., src/find, src/grep)
PIPE_EXECS = $(PIPE_SRCS:.cpp=)

# Build everything
all: $(SHELL_EXEC) $(PIPE_EXECS)

# Link main shell
$(SHELL_EXEC): $(SHELL_OBJS)
	$(CXX) $(CXXFLAGS) -o $(SHELL_EXEC) $(SHELL_OBJS)

# Compile .cpp to .o (for the shell built-ins and main)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build external pipe executables (THE FIX)
# Target: src/find, Prerequisite: src/find.cpp
src/%: src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean
clean:
	rm -f $(SHELL_EXEC) $(PIPE_EXECS) $(SHELL_OBJS)
	rm -rf src/*.dSYM

.PHONY: all clean