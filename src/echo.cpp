#include "builtins.h"
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

    //assume our file_stream is cout if redirect not true
    ostream* file_stream = &std::cout;
    ofstream output_file; //
    auto const& words = echo_options.words;
    if (echo_options.redirect){
        
        output_file.open(echo_options.redirect_file, std::ios::out);
        if (!output_file.is_open()){

            cout << "file not opened \n";
        }

        file_stream = &output_file;

        for (const auto& word: words){
            (*file_stream) << word << " ";
        }

    } else {
        for (const auto& word: words){
            (*file_stream) << word << " ";
        }
    } 

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

    //handling tokens
    vector<string> tokens;
    for (int i =0; i< argc;++i){
        tokens.push_back(argv[i]);
    }

    echo(tokens);

    return EXIT_SUCCESS;
}


