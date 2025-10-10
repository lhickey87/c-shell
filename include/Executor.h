#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include <string>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using std::string;
using std::vector;


class Executor {

    private:
        static vector<char*> to_argv(const vector<string>& args) {
            //given we are passing in a reference, what if in another function the memory is freed??
            vector<char*> argv;
            //NEEDS TO BE CLEANED UP ASAP
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

        /*static int process_pipeline(const string& command_name, const vector<string>& args){
            //are all pipes, write | read optional(write)
            int num_commands = args.size();
            
            for (int i = 0; i < num_commands; ++i){
                int fd[2];
                if (pipe(fd) == 1){
                    std::cerr << "Issue opening pipe \n";
                    return 1;
                }
            }
        } */
};



#endif