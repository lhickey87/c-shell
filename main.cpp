#include "builtins.h"
#include <dirent.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <csignal>
#include <fstream>
#include <filesystem>

std::vector<std::string> parse_line(std::string& line);

int main(){

    using namespace std;
    while (true) {
        cout << "shell>";
        string line;
        if (!getline(cin, line)){
            break;
        }

        vector<string> tokens = parse_line(line);
        auto first = tokens.begin();

        if (*first == "echo"){
            tokens.erase(first);
            echo(tokens);
        } else if (*first == "exit") {
            break;
        } else if (*first == "ls") {
            tokens.erase(first);
            ls(tokens); 
        } else if (*first == "pwd") {
            cout << "You are here" << "\n";
            cout << std::filesystem::current_path().string() <<  "\n";
        } else if (*first == "cd"){

        } 
    }
    cout << std::endl;

    return 0;
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

