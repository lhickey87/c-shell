
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <csignal>

std::vector<std::string> parse_line(std::string& line);
void echo(std::vector<std::string>& vec);

int main(){

    using namespace std;
    while (true) {
        cout << "shell>";
        string line;
        if (!getline(cin, line)){
            break;
        }

        vector<string> tokens = parse_line(line);
        auto first = tokens.begin();

        if (*first == "echo"){
            tokens.erase(first);
            echo(tokens);
        }

    }
    cout << std::endl;

    return 0;
}


std::vector<std::string> parse_line(std::string& line){

    std::stringstream ss(line);
    std::vector<std::string> tokens;
    std::string token;

    //this will loop until token is not valid, assuming this is an EOF identifier which would then stop the loop from continuing
    while (ss >> token){
        tokens.push_back(token);
    }

    return tokens;
}

//now echo needs to take in additional 
//need some file argument to be undertaken
void echo(std::vector<std::string>& vec){
    std::string ss;
    for (std::string token: vec){
        std::cout << token << " ";
    }
    std::cout << "\n";
}