#include <dirent.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <csignal>
#include <fstream>

void ls(std::vector<std::string>& vec);
std::vector<std::string> parse_line(std::string& line);
void echo(std::vector<std::string>& vec);

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
        }

    }
    cout << std::endl;

    return 0;
}


//struct dirent{
void ls(std::vector<std::string>& vec){
    //first define a pointer to a directory stream
    //loop until we find the dir name? 
    DIR* dir_stream;
    if (vec.size() < 2){
        dir_stream = opendir(".");
    } else {
        dir_stream = opendir((vec.back()).c_str());
    }
    struct dirent *dp;    
    while ((dp = readdir(dir_stream)) != NULL){
        std::cout << dp->d_name << " " << dp->d_reclen;
        std::cout << std::endl;
    }

    if (closedir(dir_stream) == -1){
        std::cout << "failed to close stream" << "\n";
    }
    
    
}

std::vector<std::string> parse_line(std::string& line){

    std::stringstream ss(line);
    std::vector<std::string> tokens;
    std::string token;

    while (ss >> token){
        tokens.push_back(token);
    }

    return tokens;
}


void echo(std::vector<std::string>& vec){
    std::string ss;
    for (std::string token: vec){
        std::cout << token << " ";
    }
    std::cout << "\n";
}