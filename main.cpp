#include "builtins.h"
#include <dirent.h>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>
#include <fstream>
#include "Executor.h"

using namespace std;
namespace fs = std::filesystem;


vector<string> parse_line(string& line);
// vector<char*> to_argv(const vector<string>& args); 
// void process_command(const string& command_name, const vector<string>& args);

int main(){

    while (true) {
        cout << fs::current_path().string() << "> ";
        string line;
        if (!getline(cin, line)){
            break;
        }
        
        vector<string> tokens = parse_line(line);
        auto first = tokens.begin();
        
        if (*first == "exit") {
            break;
        } else if (*first == "pwd") {
            cout << std::filesystem::current_path().string() <<  "\n";
        } else if (*first == "cd"){
            tokens.erase(first);
            cd(tokens);
        } else if (*first == "mkdir"){
            tokens.erase(first);
            mkdir(tokens);
        }else if (*first == "rm"){
            tokens.erase(first);
            rm(tokens); 
        }else {
            Executor::process_command(*first, tokens);
        }
    
    cout << endl;

    }

    return 0;
}

// vector<char*> to_argv(const vector<string>& args) {
//     vector<char*> argv;
//     for (auto& arg : args) {
//         argv.push_back(const_cast<char*>(arg.c_str()));
//     }
//     argv.push_back(nullptr);
//     return argv;
// }

// void process_command(const string& command_name, const vector<string>& args){
    
//     auto argv = to_argv(args);
//     std::string path = "./src/" + command_name;
//     cout << path << "\n";
    
//     pid_t pid = fork();
//     if (pid == 0) {
//         execv(path.c_str(), argv.data());
//         perror("execv failed");
//         exit(EXIT_FAILURE);
//     }
    
//     if (pid > 0) {
//         int status;
//         waitpid(pid,&status,0);
//     } else {
//         perror("fork failed");
//     }
// } 


vector<string> parse_line(string& line){
    stringstream ss(line);
    vector<string> tokens;
    string token;

    while (ss >> token){
        tokens.push_back(token);
    }

    return tokens;
}

