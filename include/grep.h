#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <functional>
#include <regex>

using namespace std;
namespace fs = std::filesystem;
using FilePath = fs::path;
using RecursiveDirIter = fs::recursive_directory_iterator;

enum class Format {DEFAULT, COUNT, FILESMATCHING, NOFILENAME};

struct Options {
    vector<string> grepArgs; //issue here is that we need to GLOB files and the pattern needs to be regex
    vector<string> outputLines;
    vector<string> filesMatching;
    vector<FilePath> globFiles;
    FilePath searchPath = fs::current_path();
    regex pattern;
    int lineCount;
    bool countOnly;
    bool noFileName;
    bool recursive;
    bool fileMatching;
    bool readStdIn;
    bool flags;
    Format format = Format::DEFAULT; 
};

using FlagHandler = std::function<void(Options&)>;
void setCountOnly(Options& options);
void setNoFileName(Options& options);
void setFilesWithMatches(Options& options);
void setRecursive(Options& options);

const unordered_map<string, FlagHandler> flag_handlers = {
    {"-c", setCountOnly}, //only return the count
    {"-h", setNoFileName}, //this should call output with no fileName
    {"-l", setFilesWithMatches}, //this should call func that only shows files that Match pattern
    {"-r", setRecursive} //everything else wouldn't have a flag so we would have the pattern and fileGlob
}; 
