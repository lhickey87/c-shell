#include "builtins.h"
#include <iostream>
#include <unistd.h>
#include <dirent.h>

#include <cstdio>   // For perror


using namespace std;

void cp(vector<string>& tokens){}

void cd(vector<string>& tokens){}

void concat(vector<string>& tokens){}

void ls(std::vector<std::string>& vec){
    DIR* dir_stream;
    struct dirent *dp;    

    if (vec.size() < 2){
        dir_stream = opendir(".");
    } else {
        dir_stream = opendir((vec.back()).c_str());
    }

    while ((dp = readdir(dir_stream)) != NULL){
        std::cout << dp->d_name << " " << dp->d_reclen;
        std::cout << std::endl;
    }

    if (closedir(dir_stream) == -1){
        std::cout << "failed to close stream" << "\n";
    }

}

void mkdir(vector<string>& tokens){


}

void pwdir() {
    // use the system-defined maximum path length
    char buffer[200];

    // attempt to get the current working directory
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        std::string path(buffer);
        
        std::cout << path << "\n";
    } else {
        perror("pwd error"); 
    }
}

void echo(vector<string>& vec){
    string ss;
    for (string token: vec){
        cout << token << " ";
    }
    cout << "\n";
}

