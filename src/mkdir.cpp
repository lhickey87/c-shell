#include "builtins.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>


using namespace std;
namespace fs = std::filesystem;


void mkdir(const vector<string>& tokens){

    if (tokens.size() == 1){
        cerr << "Need a directory arguement \n";
        return;
    }
    
    const string& token = tokens[1];
    const FilePath newPath(token);
    
    fs::create_directory(newPath);
}