#include "builtins.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>


using namespace std;
namespace fs = std::filesystem;
using Path = fs::path;
using FileInfo = fs::file_status;
using FileSize = std::uintmax_t; //defined return type of fs::file_size

struct Options {
    Path directoryPath;
    optional<FileInfo> type; 
    optional<FileSize> fileSize;
    optional<int> maxDepth;
    optional<string> nameMatch;
    optional<Path> filePath;
};

//using FlagHandler = std::function<void(Options&,vector<string>iterator&)>;
Options handleTokens(const vector<string>& tokens);
//void fileType(Options&,vector<string>iterator&);
//void fileName(Options&,vector<string>iterator&);
////void filePath(Options&,vector<string>iterator&);
//void fileSize(Options&,vector<string>iterator&);


void find(const vector<string>& tokens){
    
    Options findOptions = handleTokens(tokens);

    return;

}

Options handleTokens(const vector<string>& tokens){
    
    Options findOptions {};
    for (const auto& token : tokens){

        if (token == "find"){
            continue;
        }
    }
    return findOptions;
}



int main(int argc, char* argv[]){

    const vector<string> tokens(argv,argv+argc);

    find(tokens);

    return EXIT_SUCCESS;
}