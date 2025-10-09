#include "builtins.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include <fstream>

using namespace std;
namespace fs = std::filesystem;

struct Options {
    string inputFile;
    bool redirect = false;
    string writeFile;
};

static Options handle_flags(const vector<string>& tokens);
bool fileExists(const std::string& file);

void concat(const vector<string>& tokens){
    Options catOptions = handle_flags(tokens);

    ifstream inputFile(catOptions.inputFile);

    if (!inputFile.is_open()){
        cerr << "Could not open file: "<< catOptions.inputFile << "\n";   
    } 

    ostream* output_stream = &std::cout;

    ofstream output_file; 

    if (catOptions.redirect){
        output_file.open(catOptions.writeFile, ios::out | ios::trunc);

        if (!output_file.is_open()){
            cerr << "Cat: could not open output file: " << catOptions.writeFile << "\n";
            return;
        }
        output_stream = &output_file;
    }
    //now that we have outputstream decalred
    string line;
    while (getline(inputFile, line)){
        (*output_stream) << line << "\n";
    }
}

bool fileExists(const std::string& file){
    const fs::path newPath(file);
    return fs::exists(newPath);
}


static Options handle_flags(const vector<string>& tokens){
    Options options {};

    for (size_t i = 1; i < tokens.size();i++){
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
            options.inputFile = token;
        } 
    }

    return options;
}


int main(int argc, char* argv[]){
    vector<string> tokens(argv, argc+argv);

    concat(tokens);

    return EXIT_SUCCESS;
}