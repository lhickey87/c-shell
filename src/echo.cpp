#include "builtins.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

void echo(vector<string>& vec){
    string ss;
    for (string token: vec){
        cout << token << " ";
    }
    cout << "\n";
}