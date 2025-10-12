# Shell Implementation in C++

A custom Unix-like shell written in **C++** that supports essential features like command execution, pipes, I/O redirection, and common built-in utilities. This project provides a clear, practical example of low-level system programming.

---

## Features

* **Interactive Command Prompt**: A classic shell interface for running commands
* **Pipes (`|`)**: Chain multiple commands together, piping the output of one command to the input of the next.
* **I/O Redirection**: Redirect standard input (`<`) and standard output (`>`).
* **Built-in Commands**: Efficient, shell-internal implementations for core utilities like `cd` and `mkdir`

---

## Getting Started

### Building the Shell
1.  Clone the repository:
    ```bash
    git clone https://github.com/lhickey87/c-shell.git
    ```
2.  Navigate to the project directory:
    ```bash
    cd c-shell
    ```
3.  Compile the project using the provided `Makefile`:
    ```bash
    make
    ```
### Running the Shell
Execute the compiled binary to start the interactive session:
```bash
./my_shell
```

## Usage & Commands

The shell supports a variety of commands, which are handled in one of two ways: as shell built-ins or as external executables
### Built-in Commands
These commands are handled directly by the shell's main process, which is necessary for commands that modify the shell's state (like cd) or for performance. They are called via functions defined in the builtins.h header file.

### External Commands (Local Binaries)
These commands are compiled from their own seperate C++ source files (e.g, ls.cpp, grep.cpp) and are executed by the shell using fork()/execv() syscalls. This architecture enables full support for pipes, input/output redirection and parallel execution. 

## Examples

### Piping:
```Bash
ls | grep "*.cpp" | wc
```
### I/O Redirection:
```Bash
# Write to a file named greeting.txt
echo "Hello from shell" > greeting.txt

# USe contents of file as input for grep
grep "shell" < greeting.txt
```
