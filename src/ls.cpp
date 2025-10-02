#include "builtins.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;


//lets say someone inputs ls -l -a
//how might we deal with that
// well firstly 
struct Options {
    string path = ".";
    bool hidden = false;
    bool long_format = false;
    bool pathExists = true;
};

Options parse_options(vector<string>& tokens);

void ls(std::vector<std::string>& tokens, size_t size){

    Options lsoptions = parse_options(tokens); 

    if (!lsoptions.pathExists){
        cout << "ls: " << lsoptions.path << ": No such file or directory \n";

    } else {

        const fs::path directory(lsoptions.path);

        fs::directory_iterator di(directory);
        
        for (fs::directory_entry const& entry : di){

            string name = entry.path().filename().string();

            if (name[0] == '.' && !lsoptions.hidden){
                continue;
            }
            
            cout << name << "\n";
        } 
    }     
}

// void long_format(const fs::directory_entry& entry){

// }

Options parse_options(vector<string>& tokens){
    Options lsoptions; // this should contain default values within the struct
    for (size_t i = 0; i < tokens.size(); ++i){
        //std::vector[] will return a reference of the type
        const string& token = tokens[i];
        if (token == "-la"|| token == "-al"){
            lsoptions.hidden = true;
            lsoptions.long_format = true;
        } else if (token == "-a"){
            lsoptions.hidden = true;
        } else if (token == "-l"){
            lsoptions.long_format = true;
        } else {
            lsoptions.path = token;
            lsoptions.pathExists = fs::exists(token);
            cout << "exists: " << lsoptions.pathExists << "\n";
        }
    }
    return lsoptions;
}