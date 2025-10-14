#include "executables.h"
#include <regex>
#include <map>
#include <algorithm>
#include <regex>
#include <fstream>
#include <glob.h>


using namespace std;

struct Options {
    const char* fileGlob;
    regex pattern;
    vector<FilePath> globFiles; 
    vector<string> lines;
    int lineCount = 0;
    FilePath dirPath = FilePath(".");
};

using FlagHandler = std::function<void(Options&, TokenIterator&, const TokenIterator&)>;
Options handleTokens(const vector<string>& tokens);
using FlagHandler = std::function<void(Options&, TokenIterator&, const TokenIterator&)>;
void getMatchingFiles(Options& options, TokenIterator& it, const TokenIterator& end);
void getMatchingLines(Options& options, TokenIterator& it, const TokenIterator& end);
void searchFile(Options& options, const FilePath& filePath);

const map<string,FlagHandler> flag_handlers = {
    {"-l", getMatchingFiles},
    {"-m", getMatchingLines}
};

void grep(const vector<string>& tokens){
    Options opts = handleTokens(tokens);

    for (const auto& line : opts.lines){
        cout << line << "\n";
    }
}

Options handleTokens(const vector<string>& tokens){
    Options opts {};

    auto end = tokens.end();

    auto it = tokens.begin();
    
    while (it != end){

        const string& token = *it; //dereferncing to get token string value

        if (token == "grep"){
            ++it;
            continue; 
        }

        auto handler = flag_handlers.find(token);

        if (handler != flag_handlers.end()){

            handler->second(opts, it, end);
        }
        ++it;
    }

    return opts;
}

void getMatchingFiles(Options& options, TokenIterator& it, const TokenIterator& end){
    ++it;
    if (it != end){
        options.fileGlob = (*it).c_str(); 
    }

    glob_t globStruct;

    std::memset(&globStruct,0,sizeof(glob_t));

    int returnVal = glob(options.fileGlob, 0, nullptr, &globStruct);

    if (returnVal != 0) {
        if (returnVal != GLOB_NOMATCH) {
            globfree(&globStruct);
            cerr << "glob() failed \n";
        }
    }

    for (size_t i =0; i < globStruct.gl_pathc; ++i){
        FilePath matchingFile = FilePath(globStruct.gl_pathv[i]);
        options.globFiles.push_back(matchingFile);
    }

    globfree(&globStruct);
}

void getMatchingLines(Options& options, TokenIterator& it, const TokenIterator& end){
    ++it;
    if (it != end){
        options.pattern = regex(*it);
    } else {
        cerr << "end of iterator \n";
        return;
    }

    for (const auto& file : options.globFiles){
        searchFile(options, file);
    }
}


void searchFile(Options& options, const FilePath& filePath){
    ifstream inputFile(filePath); 

    string fileString = filePath.filename().string();

    if (!inputFile.is_open()){
        cerr << "issue opening file" << filePath.filename().string() << "\n";
        return;
    }

    string line;
    while (getline(inputFile,line)){
        if (regex_search(line, options.pattern)){
            options.lineCount++; //adding 1 for each line matchged
            options.lines.push_back(fileString+":"+line);
        }
    }
}


int main(int argc, char* argv[]){

    vector<string> tokens(argv,argv+argc);

    grep(tokens);

    return EXIT_SUCCESS;
}