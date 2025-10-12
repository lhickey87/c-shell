#include "executables.h"
#include <fstream>

using std::string;
using std::vector;

struct Options {
    string inputFile = "";
};

Options handleTokens(const vector<string>& tokens);

void wc(const vector<string>& tokens) {
    Options opts = handleTokens(tokens);
    
    std::istream* input = &std::cin;  // Default to stdin
    std::ifstream fileStream;
    
    if (!opts.inputFile.empty()) {
        fileStream.open(opts.inputFile);
        if (!fileStream.is_open()) {
            std::cerr << "could not open file: " << opts.inputFile << "\n";
            return;
        }
        input = &fileStream;
    }
    
    string line;
    int count = 0;
    while (getline(*input, line)) {
        count++;
    }
    
    std::cout << count << "\n";
}

Options handleTokens(const vector<string>& tokens){
    Options options {};
    for (const auto& token : tokens){
        if (token == "wc"){ continue;}
        options.inputFile = token;
    }

    return options;
}


int main(int argc, char* argv[]){
    const vector<string> tokens(argv, argv+argc);
    wc(tokens);

    return EXIT_SUCCESS;
}