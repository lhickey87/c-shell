#include "builtins.h"
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

struct Options {
    string input_files;
    bool redirect = false;
    string writeFile;
};

static Options handle_flags(const vector<string>& tokens);
bool fileExists(const std::string& file);

void concat(const vector<string>& tokens){
    Options catOptions = handle_flags(tokens);
    cout << "inside function! \n"; 

    const std::string& file = catOptions.input_files;
    ifstream input_file(file);

    std::string line;

    ostream* output_stream = &std::cout;

    ofstream output_file; 

    if (!catOptions.redirect) {

        while (getline(input_file, line)){
            cout << line << "\n";
        }

    } else {
        //in the case redirect is true, we must use ofstream instead of std::cout as the output 
        output_file.open(catOptions.writeFile, ios::out | ios::trunc);

        if (!output_file.is_open()){ cout << "file not open \n";}
        //now that the file is open should change output_stream from referencing std::cout to current file

        output_stream = &output_file;

        while (getline(input_file, line)){
            (*output_stream) << line << "\n";
        }

        input_file.close();
    }
}

bool fileExists(const std::string& file){
    const fs::path newPath(file);
    return fs::exists(newPath);
}


static Options handle_flags(const vector<string>& tokens){
    Options options;

    for (size_t i = 0; i < tokens.size();i++){
        const string& token = tokens[i];

        if (token == "cat"){
            continue;
        }

        if (token == ">"){
            options.redirect = true;
            if (i+1 < tokens.size()){
                options.writeFile = tokens[i+1];
                i++;
            } else {
                std::cerr << "No output file \n";
            }
        } else if (!options.redirect && fileExists(token)){
            options.input_files = token;
        } 
    }

    return options;
}