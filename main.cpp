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

int main(){

    auto absolute = fs::current_path().string() + "/";

    while (true) {
        cout << fs::current_path().string() << "> ";
        string line;
        if (!getline(cin, line)){
            break;
        }
        
        const vector<string> tokens = parse_line(line);
        auto first = tokens.begin();
        
        if (*first == "exit") {
            break;
        } else if (*first == "pwd") {
            cout << fs::current_path().string() <<  "\n";
        } else if (*first == "cd"){
            cd(tokens);
        } else if (*first == "mkdir"){
            mkdir(tokens);
        }else if (*first == "rm"){
            rm(tokens); 
        }else {
            
            Executor::process_command(absolute, *first, tokens);
        }
    
    cout << endl;

    }

    return EXIT_SUCCESS;
}


vector<string> parse_line(string& line){
    stringstream ss(line);
    vector<string> tokens;
    string token;

    while (ss >> token){
        tokens.push_back(token);
    }

    return tokens;
}

