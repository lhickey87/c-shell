#include "builtins.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

void ls(std::vector<std::string>& tokens, size_t size){

    if (size == 0){
        tokens.push_back(".");
    }

    auto it = tokens.begin();

    if (fs::exists(*it)) {

        const fs::path directory(*it);

        fs::directory_iterator di(directory);
        
        for (fs::directory_entry const& entry : di){

            string name = entry.path().filename().string();

            if (name[0] == '.'){
                continue;
            }

            if (entry.is_regular_file()){

                cout << name << " size: " << entry.file_size() <<"\n";

            } else if (entry.is_directory()){

                cout << name << "\n";
            }
        } 
        
    } else {
        cout << "ls: " << *it << ": " << "No such file or directory\n";
    }
    
}