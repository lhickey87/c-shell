#include "executables.h"
#include <regex>
#include <map>


using namespace std;

struct Options {
    regex fileGlob;
    optional<int> count; //if -c command is used 
    bool onlyFile; //if true we can add to filesMatching, if false add to filesNotMatching vec
    vector<FilePath> filesMatching; 
    vector<FilePath> filesNotMatching; //any files not matching would be added here if flag is present
    bool recursive;
    bool nonMatchingLines; //if -v flag used set to true
};

Options handleTokens(const vector<string>& tokens);

using FlagHandler = std::function<void(Options&, TokenIterator&, const TokenIterator&)>;

void getLineCount(Options&, TokenIterator&, const TokenIterator&);

void getMatchingFiles(Options&, TokenIterator&, const TokenIterator&);

void invertLineMatch(Options&, TokenIterator&, const TokenIterator&);

const map<string,FlagHandler> flag_handlers = {
    {"-c", getLineCount},
    {"-l", getMatchingFiles},
    {"-L", getMatchingFiles},
    {"-v", invertLineMatch} 
};

void grep(const vector<string>& tokens){


}

Options handleTokens(const vector<string>& tokens){

}

void getLineCount(Options&, TokenIterator&, const TokenIterator&){}


void getMatchingFiles(Options&, TokenIterator&, const TokenIterator&){}

void invertLineMatch(Options&, TokenIterator&, const TokenIterator&){}



int main(int agrc, char* argv[]){

}