#include "builtins.h"
#include "Executor.h"
#include <sstream>
#include <unistd.h>
#include <fstream>
#include <iterator>

using namespace std;
namespace fs = std::filesystem;


using Commands = vector<Command>;
Command tokenize(const string& command);
Commands parse_line(const string& line);

int main(){

    auto absolute = fs::current_path().string()+ "/";

    while (true) {
        cout << fs::current_path().string() << "> ";
        string line;
        if (!getline(cin, line)){
            break;
        }

        Commands commands = parse_line(line);
        if (commands.empty()){
            continue;
        }

        if (commands.size() > 1){
            Executor::process_pipeline(absolute, commands);
            continue;
        }
        
        string cmd = commands[0].commandName;  
        vector<string> tokens = commands[0].args;
        if (cmd == "exit") {
            break;
        } else if (cmd == "pwd") {
            cout << fs::current_path().string() <<  "\n";
        } else if (cmd == "cd"){
            cd(tokens);
        } else if (cmd == "mkdir"){
            mkdir(tokens);
        }else if (cmd == "rm"){
            rm(tokens); 
        }else {
            Executor::process_command(absolute, cmd, tokens);
        }

    }

    return EXIT_SUCCESS;
}

//returns individual Command struct
Command tokenize(const string& cmdString){
    stringstream ss(cmdString);
    vector<string> args {istream_iterator<string>(ss), istream_iterator<string>()};
    if (args.empty()){
        return {"",{}};
    }
    return Command{args[0], args};
}


Commands parse_line(const string& line) {
    size_t pipeIndex = line.find("|");
    Commands commands;

    if (pipeIndex == string::npos){
        commands.push_back(tokenize(line));
    } else {
        commands.push_back(tokenize(line.substr(0, pipeIndex)));
        commands.push_back(tokenize(line.substr(pipeIndex+1)));
    }

    return commands;
}