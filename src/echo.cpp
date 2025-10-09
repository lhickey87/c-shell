#include "builtins.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include <fstream>

using namespace std;
namespace fs = std::filesystem;

struct EchoOptions{
    bool redirect = false;
    std::vector<string> words;
    std::string redirect_file;
    bool has_error = false;
};

static EchoOptions handle_tokens(const vector<string>& tokens);

void echo(const vector<string>& tokens){
    EchoOptions echo_options = handle_tokens(tokens);

    ostream* file_stream = &std::cout;
    
    std::ofstream output_file;
    if (echo_options.redirect){
        output_file.open(echo_options.redirect_file, ios::out | ios::trunc);
        
        if (!output_file.is_open()){
            cerr << "file not opened \n";
        }

        file_stream = &output_file;
    }

    for (const auto& word: echo_options.words){
        (*file_stream) << word << " ";
    }

    (*file_stream) << endl;
    
}

static EchoOptions handle_tokens(const vector<string>& tokens){

    EchoOptions options {};
    for (size_t i = 1; i < tokens.size(); ++i) {
        const auto& token = tokens[i];

        if (token == ">") {
            options.redirect = true;
            
            if (++i < tokens.size()) {
                options.redirect_file = tokens[i];
                break; 
            } else {
                std::cerr << "shell: syntax error: redirect file missing after '>'\n";
                options.has_error = true;
                break; 
            }
        } 
        else {
            options.words.push_back(token);
        }
    }
    return options;
}

int main(int argc, char* argv[]){

    const vector<string> tokens(argv,argv+argc);

    echo(tokens);

    return EXIT_SUCCESS;
}


