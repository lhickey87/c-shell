#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include <string>
#include <sys/wait.h>
#include <iostream>

class Executor {

    private:
        static std::vector<char*> to_argv(const std::vector<std::string>& args) {
            //given we are passing in a reference, what if in another function the memory is freed??
            std::vector<char*> argv;
            for (auto& arg : args) {
                argv.push_back(const_cast<char*>(arg.c_str()));
            }
            argv.push_back(nullptr);
            return argv;
        }

    public:
        static int process_command(const std::string& path, const std::string& command_name, const std::vector<std::string>& args){ 
            auto argv = to_argv(args);

            std::string command_path = path +"/src/"+ command_name;

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
};


#endif