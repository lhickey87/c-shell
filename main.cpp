#include "builtins.h"
#include <dirent.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

std::vector<std::string> parse_line(std::string& line);

int main(){

    while (true) {
        cout << fs::current_path().string() << "> ";
        string line;
        if (!getline(cin, line)){
            break;
        }
        
        //need to turn token vector into c-style strings for exec() syscall
        vector<string> tokens = parse_line(line);
        auto first = tokens.begin();
        
        if (*first == "echo"){
            tokens.erase(first);
            echo(tokens);
        } else if (*first == "exit") {
            break;
        } else 
        if (*first == "ls") {
            //CAN BE PIPED FROM
            //do we have to create a child process here?
            //need to create function to handle this
            int pid = fork();
            if (pid < 0){cout << "error forking \n";}
            if (pid == 0){
                cout << "inside child process \n";
                execl("./src/ls","ls", "-l",NULL);

                perror("exec failed");

                exit(EXIT_FAILURE);
            }

            int status;
            waitpid(pid, &status, 0);
        } else if (*first == "pwd") {
            //piping allowed
            cout << std::filesystem::current_path().string() <<  "\n";
        } else if (*first == "cd"){
            //piping not allowed
            tokens.erase(first);
            cd(tokens);
        } else if (*first == "mkdir"){
            //CANNOT BE USED IN PIPES
            tokens.erase(first);
            mkdir(tokens);
        } else if (*first == "cat"){
            concat(tokens);
        }else if (*first == "rm"){
            //requires xargs
            tokens.erase(first);
            rm(tokens); 
        }else {
            cout << "Command: " << *first << " not recognized";
        }
    
    cout << std::endl;

    }

    return 0;
}

// void pipe(std::string cmd1, std::string cmd2){
//     int fd[2];
//     if (pipe(fd)==-1){
//         cout << "error happened \n";
//         return 1;
//     }

//     //whatever called fork is the main process, this main process will be respondible for forking the first and second command
//     //and dealing with the pipe
//     int pid1 = fork();
//     if (pid1 < 0){
//         cout << "process failed to star \n";
//         return 2;
//     }

//     if (pid1 == 0){
//         close(fd[0]);
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[1]);
//         //exec()
//     }

//     int pid2 = fork();
//     if (pid2 < 0){
//         cout << "process failed to star \n";
//         return 2;
//     }

//     if (pid2 == 0){
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         //exec()
//     }

//    //finish
// }
void func(){
    int pid = fork();
    if (pid < 0){cout << "error forking \n";}
    if (pid == 0){
        cout << "inside child process \n";
        execl("./src/ls","ls", "-l",NULL);

        perror("exec failed");

        exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid, &status,0);
}

//the biggest decision will actually be how to handle individual tokens
// a user entering ls -l -a is the same as ls -la
std::vector<std::string> parse_line(std::string& line){

    std::stringstream ss(line);
    std::vector<std::string> tokens;
    std::string token;

    while (ss >> token){
        tokens.push_back(token);
    }

    return tokens;
}

