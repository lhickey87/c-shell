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
bool fileExists(const std::string& file);

void concat(vector<string>& tokens){
    Options catOptions = handle_flags(tokens);
    cout << "inside function! \n"; 

    const std::string& file = catOptions.input_files[0];
    ifstream input_file(file);

    if (!input_file.is_open()){
        cout << "not open \n";
    }

    if (!catOptions.redirect) {
        std::string line;
        while (getline(input_file, line)){
            cout << line << "\n";
        }
    }
}

bool fileExists(const std::string& file){
    cout << "inside file exists path \n";
    const fs::path& newPath(file);
    cout << fs::exists(newPath) << "\n";
    return fs::exists(newPath);
}


Options handle_flags(vector<string>& tokens){
    Options options;
    //the tokens variable is a reference to a vector of strings which are our tokens
    //thus to iterate over it we can do range based for loop with auto const& token: tokens
    for (size_t i = 0; i < tokens.size();i++){
        const string& token = tokens[i];

        if (token == ">"){
            options.redirect = true;
            if (i+1 < tokens.size()){
                options.writeFile = tokens[i+1];
                i++;
            } else {
                std::cerr << "No output file \n";
            }
        } else if (!options.redirect && fileExists(token)){
            options.input_files.push_back(token);
        }
    }

    return options;
}