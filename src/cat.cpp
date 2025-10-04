#include "builtins.h"
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;


struct Options {
    vector<string> input_files;
    bool redirect = false;
    string writeFile;
};

Options handle_flags(vector<string>& tokens);

//this is mainly what needs work, need to handle redirection
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



Options handle_flags(vector<string>& tokens){
    Options options;    
    //in this case we need to open a file, does relative path work?
    const fs::path& token = tokens[0];
    options.readFile = token.string();
    cout << token;
    return options;
}