#include "executables.h"
#include <algorithm>
#include <fstream>
#include <glob.h>
#include "grepConfig.h"
using namespace std;


Options handleTokens(const vector<string>& tokens) {
    Options opts;
    size_t i = 1;
    
    while (i < tokens.size() && tokens[i][0] == '-') {
        if (tokens[i] == "-c") opts.showCountOnly = true;
        else if (tokens[i] == "-l" && ++i < tokens.size()) opts.fileGlobArg = tokens[i];
        i++;
    }
    
    if (i < tokens.size()) opts.patternArg = tokens[i++];
    
    if (opts.fileGlobArg.empty() && i < tokens.size()) {
        opts.fileGlobArg = tokens[i];
    }
    
    return opts;
}

void findMatchingFiles(Options& opts) {
    glob_t glob_result;
    memset(&glob_result, 0, sizeof(glob_t));

    int globSuccess = glob(opts.fileGlobArg.c_str(), 0, nullptr, &glob_result);
    
    if (globSuccess == 0) {
        for (size_t i = 0; i < glob_result.gl_pathc; ++i) {
            opts.globFiles.emplace_back(glob_result.gl_pathv[i]);
        }
    }
    
    globfree(&glob_result);
}

void searchFile(Options& opts, const FilePath& path) {
    ifstream file(path);
    if (!file) return;
    
    string filename = path.filename().string();
    string line;
    
    while (getline(file, line)) {
        if (regex_search(line, opts.pattern)) {
            opts.lineCount++;
            opts.lines.push_back(filename + ":" + line);
        }
    }
}

void searchAllFiles(Options& opts) {
    try {
        opts.pattern = regex(opts.patternArg);
    } catch (const regex_error&) {
        cerr << "grep: invalid pattern\n";
        return;
    }
    
    for (const auto& file : opts.globFiles) {
        searchFile(opts, file);
    }
}


void grep(const vector<string>& tokens) {
    Options opts = handleTokens(tokens);
    
    if (opts.fileGlobArg.empty() || opts.patternArg.empty()) {
        cerr << "Usage: grep [-c] pattern files\n";
        return;
    }
    
    findMatchingFiles(opts);
    searchAllFiles(opts);
    
    if (opts.showCountOnly) {
        cout << opts.lineCount << "\n";
    } else {
        for (const auto& line : opts.lines) {
            cout << line << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    grep(vector<string>(argv, argv + argc));
    return EXIT_SUCCESS;
}