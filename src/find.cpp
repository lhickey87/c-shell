#include "executables.h"
#include <map>
#include <functional>
#include <regex>
#include "glob.h"

using namespace std;

struct Options {
    FilePath directoryPath = FilePath(".");
    optional<FileType> type; 
    optional<FileSize> fileSize;
    optional<int> maxDepth;
    optional<regex> nameMatch;
    optional<FilePath> filePath;
};
//should we use templating
//template<T>
//function(T&& ... v){} this way it handles many options of different types
//then based on type we would know how to check all vars

using FlagHandler = function<void(Options&, TokenIterator&, const TokenIterator&)>;

using RecursiveDirIter = fs::recursive_directory_iterator;

Options handleTokens(const vector<string>& tokens);

void handleName(Options& options, TokenIterator& it, const TokenIterator& end);

void handleSize(Options& options, TokenIterator& it, const TokenIterator& end);

void handleType(Options& options, TokenIterator& it, const TokenIterator& end);

void handleMaxDepth(Options& options, TokenIterator& it, const TokenIterator& end);

bool FileMatches(DirectoryEntry& dirEntry, const Options& options);

//this will be a hard function to implement
//could use std::copy_if but the issue is which predicate do we use
vector<DirectoryEntry> FindFiles(const Options& options);


void find(const vector<string>& tokens){
    
    Options findOptions = handleTokens(tokens);
   
    vector<DirectoryEntry> matchingFiles = FindFiles(findOptions);

    for (const auto& file : matchingFiles){
        cout << "inside matching loop \n";
        cout << fs::absolute(file.path()) << "\n"; 
    }

    return;
}

const map<string, FlagHandler> flag_handlers = {
    {"-name", handleName},
    {"-type", handleType},
    {"-size", handleSize},
    {"-maxdepth", handleMaxDepth}
};

Options handleTokens(const vector<string>& tokens){
    Options findOptions {};
    auto it = tokens.begin();
    auto end = tokens.end();

    while (it != end){
        const string& token = *it; //dereferncing to get token string value

        if (token == "find"){
            ++it;
            continue; 
        }
        //find what flag was passed
        auto handler = flag_handlers.find(token);
        if (handler != flag_handlers.end()){
            handler->second(findOptions, it, end);
        } else if (!token.empty()){
            //token will be a reference to string, which can be passed into the fs::filepath constructor
            findOptions.directoryPath = FilePath(token); 
        }
        ++it;
    }

    return findOptions;
}

void handleName(Options& options, TokenIterator& it, const TokenIterator& end) {
    ++it;  // Move past the flag
    if (it != end) {
        options.nameMatch = regex(*it);
    } else {
        throw runtime_error("find: -name requires an argument");
    }
}

void handleType(Options& options, TokenIterator& it, const TokenIterator& end) {
    ++it;
    if (it != end) {
        char type_char = (*it)[0];
        switch (type_char) {
            case 'f': options.type = FileType::regular; break;
            case 'd': options.type = FileType::directory; break;
            case 'l': options.type = FileType::symlink; break;
            default: throw runtime_error("find: invalid file type");
        }
    } else {
        throw runtime_error("find: -type requires an argument");
    }
}

void handleSize(Options& options, TokenIterator& it, const TokenIterator& end) {
    ++it;
    if (it != end) {
        options.fileSize = stoul(*it);  
    } else {
        throw runtime_error("find: -size requires an argument");
    }
}

void handleMaxDepth(Options& options, TokenIterator& it, const TokenIterator& end) {
    ++it;
    if (it != end) {
        options.maxDepth = stoi(*it);
    } else {
        throw runtime_error("find: -maxdepth requires an argument");
    }
}

vector<DirectoryEntry> FindFiles(const Options& options) {
    vector<DirectoryEntry> results;
    
    for (const auto& entry : RecursiveDirIter(options.directoryPath)) {
        
        if (options.nameMatch) {
            string filename = entry.path().filename().string();
            if (!regex_match(filename, *options.nameMatch)) {
                continue;
            }
        }
        
        // Check file type
        if (options.type) {
            if (entry.status().type() != *options.type) {
                continue;
            }
        }
        
        // Check size
        if (options.fileSize) {
            if (entry.file_size() != *options.fileSize) {
                continue;
            }
        }
        
        results.push_back(entry);
    }
    
    return results;
}


int main(int argc, char* argv[]){

    const vector<string> tokens(argv,argv+argc);

    find(tokens);

    return EXIT_SUCCESS;
}