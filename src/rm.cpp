#include "builtins.h"
#include <filesystem>
#include <iostream>


using namespace std;
namespace fs = std::filesystem;

struct Options {
    bool is_file = false;
    bool is_directory = false;
    vector<string> flags;
};

Options handle_tokens(const vector<string>& tokens);


void rm(const vector<string>& tokens){
    Options newopts = handle_tokens(tokens);
    return;
}

Options handle_tokens(const vector<string>& tokens){

    Options options {};
    for (auto const& token: tokens){
        const fs::path& newPath(token);
        if (fs::is_regular_file(newPath)){
            options.is_file = true;
            cout << "regular file \n";
        } else if (fs::is_directory(newPath)){
            options.is_directory = true;
            cout << "direcotry \n";
        } else {
            cout << "something else \n";
        }
    }

    return options; 
}