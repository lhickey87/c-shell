#include "builtins.h"


using namespace std;
namespace fs = std::filesystem;


void find(vector<string>& tokens){
    cout << tokens[0] << "\n";
    return;
}

int main(int argc, char* argv[]){

    vector<string> tokens;
    for (int i = 0;i < argc; ++i){
        tokens.push_back(argv[i]);
    }

    find(tokens);

    return EXIT_SUCCESS;
}