#include "builtins.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;


void mkdir(vector<string>& tokens){
    //typically only one flag such as -p (means to also create the parent directory if user enters say mkdir -p src/test)
    //the token passed in SHOULD represent the path, lets first begin assuming path is correct
    const string& token = tokens[0];
    const fs::path newPath(token);
    //now what even is path, is it a pointer, a reference or a value itself??
    fs::create_directory(newPath);
}