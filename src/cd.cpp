#include "builtins.h"

using namespace std;
namespace fs = std::filesystem;


void cd(vector<string>& tokens){
    const fs::path& newPath(tokens[0]);
    fs::current_path(newPath);
}