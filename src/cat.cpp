#include "builtins.h"
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;


struct Options {
    string path;
    bool redirect = false;
    string readFile;
    string writeFile;
};
Options handle_flags(vector<string>& tokens);


void concat(vector<string>& tokens){
    Options cat_options = handle_flags(tokens);
    filebuf newfile;
    //should readFile be type fs::path&?
    newfile.open(cat_options.readFile);
    char arr[20];

    int amount = newfile.sgetn(arr, 19);
    cout << arr << "\n";
    cout << newfile.is_open() << "\n";

    return;
}



//assume at first this only includes ONE file path just to be read
Options handle_flags(vector<string>& tokens){
    Options options;    
    //in this case we need to open a file, does relative path work?
    const fs::path& token = tokens[0];
    options.readFile = token.string();
    cout << token;
    return options;
}