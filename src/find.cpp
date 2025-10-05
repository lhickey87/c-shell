#include "builtins.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;


void find(vector<string>& tokens){
    cout << tokens[0] << "\n";
    return;
}