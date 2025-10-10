#include "executables.h"
#include <fstream>

using namespace std;

struct CatOptions {
    string inputFile;
    bool redirect = false;
    string writeFile;
};
using OutputStream = std::ostream;
using OutputFile = std::ofstream;

static CatOptions handleTokens(const vector<string>& tokens);
bool fileExists(const std::string& file);

void concat(const vector<string>& tokens){
    CatOptions catOptions = handleTokens(tokens);

    ifstream inputFile(catOptions.inputFile);

    if (!inputFile.is_open()){
        cerr << "Could not open file: "<< catOptions.inputFile << "\n";   
    } 

    OutputStream* output_stream = &std::cout;

    OutputFile output_file; 

    if (catOptions.redirect){
        output_file.open(catOptions.writeFile, ios::out | ios::trunc);

        if (!output_file.is_open()){
            cerr << "Cat: could not open output file: " << catOptions.writeFile << "\n";
            return;
        }
        output_stream = &output_file;
    }
    
    string line;
    while (getline(inputFile, line)){
        (*output_stream) << line << "\n";
    }
}

bool fileExists(const std::string& file){
    const FilePath newPath(file);
    return fs::exists(newPath);
}


static CatOptions handleTokens(const vector<string>& tokens){
    CatOptions options {};

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