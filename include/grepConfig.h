#pragma once
#include <string>
#include <vector>
#include <regex>
#include <filesystem>
#include <functional>

// 1. Define namespace alias first
namespace fs = std::filesystem;
// 2. Then use the alias to define the type
using FilePath = fs::path;

struct Options {
    std::string patternArg = ""; 
    // ensures c_str() call is safe even if not set.
    std::string fileGlobArg = ""; 
    std::regex pattern;
    std::vector<FilePath> globFiles;
    std::vector<std::string> lines;
    int lineCount = 0;
    bool showCountOnly = false;
    bool showLines = false; // Default behavior
    bool readStdIn = false; //for piping
};


Options handleTokens(const std::vector<std::string>& tokens);
void findMatchingFiles(Options& options);
void searchFile(Options& options, const FilePath& filePath);
void searchAllFiles(Options& options);

