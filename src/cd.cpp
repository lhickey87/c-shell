#include "builtins.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;


void cd(const vector<string>& tokens){
    if (tokens.size() == 1){
        cerr << "need directory arguement \n";
        return;
    }

    const fs::path& newPath(tokens[1]);
    fs::current_path(newPath);
}