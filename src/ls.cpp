#include "builtins.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;
 
struct Options {
    string path = ".";
    bool hidden = false;
    bool long_format = false;
    bool pathExists = true;
};

Options parse_options(const vector<string>& tokens);

void ls(const vector<string>& tokens) {
    
    Options lsoptions = parse_options(tokens);
    if (!lsoptions.pathExists){
        std::cout << "ls: " << lsoptions.path << ": No such file or directory \n";
        return; // Exit function early
    } 

    const fs::path directory(lsoptions.path);

    if (!fs::is_directory(directory)) {
        // Path exists but is a file (e.g., 'ls Makefile')
        std::cout << lsoptions.path << "\n";
        return; 
    }

    try {
        fs::directory_iterator di(directory);
        
        for (fs::directory_entry const& entry : di){
            std::string name = entry.path().filename().string();

            if (name[0] == '.' && !lsoptions.hidden){
                continue; 
            }
            
            // For now, only output name (implement long_format later)
            std::cout << name << "\n";
        } 
    } catch (const fs::filesystem_error& e) {
        std::cerr << "ls: error accessing " << lsoptions.path << ": " << e.what() << "\n";
    }
}


Options parse_options(const vector<string>& tokens){
    Options lsoptions {}; // this should contain default values within the struct
    for (size_t i = 0; i < tokens.size(); i++){
        auto const& token = tokens[i];
        if (token == "ls"){
            continue;
        } 
        //this loop should NOT change path if we only have ls -a, or ls -l
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
        }
    }
    
    return lsoptions;
}