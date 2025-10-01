#include "builtins.h"
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <filesystem>
#include <cstdio>   // For perror

//the idea the std::filesystem is that thgere exists s

using namespace std;
namespace fs = std::filesystem;

void cp(vector<string>& tokens){}

void cd(vector<string>& tokens){}

void concat(vector<string>& tokens){}

void ls(std::vector<std::string>& tokens){

    auto it = tokens.begin();
    if (fs::exists(*it)) {
        cout << "directory is: " << *it << "\n";
        const fs::path directory(*it);
        fs::directory_iterator di(directory);
        
        //is entry of type directory_entry?
        for (fs::directory_entry const& entry : di){
            if (entry.is_regular_file()){
                cout << entry.path().filename() << " size: " << entry.file_size() <<"\n";
            }
        } 
        
    } else {
        cout << "ls: " << *it << ": " << "No such file or directory\n";
    }
    
}
// void ls(std::vector<std::string>& vec){
//     dir* dir_stream;
//     struct dirent *dp;    

//     if (vec.size() < 2){
//         dir_stream = opendir(".");
//     } else {
//         dir_stream = opendir((vec.back()).c_str());
//     }

//     while ((dp = readdir(dir_stream)) != null){
//         std::cout << dp->d_name << " " << dp->d_reclen;
//         std::cout << std::endl;
//     }

//     if (closedir(dir_stream) == -1){
//         std::cout << "failed to close stream" << "\n";
//     }

// }

void mkdir(vector<string>& tokens){


}

void find(vector<string>& tokens){
    
}

void pwdir() {
    char buffer[200];

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

