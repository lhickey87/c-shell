CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

SRC_DIR = src

SHELL_EXEC = myshell

BUILTIN_SRCS = $(SRC_DIR)/mkdir.cpp $(SRC_DIR)/cd.cpp $(SRC_DIR)/rm.cpp
SHELL_SRC = main.cpp $(BUILTIN_SRCS)

ALL_SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

PIPE_SRCS = $(filter-out $(BUILTIN_SRCS), $(ALL_SRC_FILES))

PIPE_EXECS = $(PIPE_SRCS:.cpp=)

SHELL_OBJS = $(SHELL_SRC:.cpp=.o)

all: $(SHELL_EXEC) $(PIPE_EXECS)

$(SHELL_EXEC): $(SHELL_OBJS)
	@echo "Linking shell executable..."
	$(CXX) $(CXXFLAGS) -o $(SHELL_EXEC) $(SHELL_OBJS)

%.o: %.cpp
	@echo "Compiling $< into $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SRC_DIR)/%: $(SRC_DIR)/%.cpp
	@echo "Building $@ executable..."
	$(CXX) $(CXXFLAGS) -o $@ $

clean:
	rm -f $(SHELL_EXEC) $(PIPE_EXECS) $(SHELL_OBJS)
	rm -rf $(SRC_DIR)/*.dSYM *.dSYM

.PHONY: all clean