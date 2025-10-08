#include "builtins.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>


using namespace std;
namespace fs = std::filesystem;


void find(const vector<string>& tokens){
    cout << tokens[0] << "\n";
}

int main(int argc, char* argv[]){

    const vector<string> tokens(argv,argv+argc);

    find(tokens);

    return EXIT_SUCCESS;
}