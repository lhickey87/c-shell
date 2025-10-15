#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include <string>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using std::string;
using std::vector;


struct Command {
    string commandName;
    vector<string> args;
};
using Commands = vector<Command>;

class Executor {

    private:
        static vector<char*> to_argv(const vector<string>& args) {

            vector<char*> argv;

            for (auto& arg : args) {
                argv.push_back(const_cast<char*>(arg.c_str()));
            }
            argv.push_back(nullptr);
            return argv;
        }

    public:
        static int process_command(const string& path, const string& command_name, const vector<string>& args){ 
            auto argv = to_argv(args);

            string command_path = path +"/src/"+ command_name;

            pid_t pid = fork();
            if (pid == 0) {
                execv(command_path.c_str(), argv.data());
                perror("execv failed");
                exit(EXIT_FAILURE);
            }
            
            if (pid > 0) {
                int status;
                waitpid(pid, &status, 0);
            } else {
                perror("fork failed");
            }
            return 0;
        }

        static int process_pipeline(const string& path, const Commands& commands) {
            int num_commands = commands.size();
            int prev_pipe_read = -1;  // Track previous pipe's read end
            
            for (int i = 0; i < num_commands; ++i) {
                int pipe_fds[2];
                
                if (i < num_commands - 1) {
                    if (pipe(pipe_fds) == -1) {
                        perror("pipe");
                        return 1;
                    }
                }
                
                pid_t pid = fork();
                
                if (pid == -1) {
                    perror("fork");
                    return 1;
                }
                
                if (pid == 0) {  // Child process
                    if (prev_pipe_read != -1) {
                        dup2(prev_pipe_read, STDIN_FILENO);
                        close(prev_pipe_read);
                    }
                    
                    if (i < num_commands - 1) {
                        dup2(pipe_fds[1], STDOUT_FILENO);
                        close(pipe_fds[1]);
                        close(pipe_fds[0]);
                    }
                    
                    string command_path = path + "/src/" + commands[i].commandName;
                    auto argv = to_argv(commands[i].args);
                    
                    execv(command_path.c_str(), argv.data());
                    perror("execv");
                    exit(1);
                }
                
                if (prev_pipe_read != -1) {
                    close(prev_pipe_read);
                }
                
                if (i < num_commands - 1) {
                    close(pipe_fds[1]);
                    prev_pipe_read = pipe_fds[0];
                }
            }
            

            for (int i = 0; i < num_commands; ++i) {
                wait(nullptr);
            }
            
            return 0;
        } 
};

#endif