#include "builtins.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

struct Options {
    string path = ".";
    bool hidden = false;
    bool long_format = false;
    bool pathExists = true;
};

static Options parse_options(const vector<string>& tokens);
void long_format(const fs::directory_entry& entry);
void print_perms(std::filesystem::perms perms);
void hidden(const std::string& name);


void ls(const vector<string>& tokens) {
    
    Options lsoptions = parse_options(tokens);
    if (!lsoptions.pathExists){
        std::cout << "ls: " << lsoptions.path << ": No such file or directory \n";
        return; 
    } 

    const fs::path directory(lsoptions.path);

    if (!fs::is_directory(directory)) {
        // Path exists but is a file (e.g., 'ls Makefile')
        std::cout << lsoptions.path << "\n";
        return; 
    }

    try {
        fs::directory_iterator di(directory);
        
        for (fs::directory_entry const& entry : di){
            
            const string name = entry.path().filename().string();

            if (lsoptions.long_format && lsoptions.hidden){

                long_format(entry); 

            } else if (lsoptions.long_format){

                if (name[0]== '.'){ continue;}

                long_format(entry); 
            } else {
                hidden(name);
            }

            } 
        } catch (const fs::filesystem_error& e) {
        std::cerr << "ls: error accessing " << lsoptions.path << ": " << e.what() << "\n";
    }
}


void hidden(const std::string& name){
    std::cout << name << '\n';
}

void long_format(const fs::directory_entry& entry){
    const fs::path p = entry.path();
    try {
        fs::file_status status = fs::status(p);
        fs::perms file_perms = status.permissions();
        print_perms(file_perms);
        cout << " " << entry.path().filename().string() << "\n";
    } catch (const fs::filesystem_error& e){
        cerr << "Error: " << e.what() << "\n";
    }
}

void print_perms(std::filesystem::perms p) {
    using std::filesystem::perms;
    std::cout << ((p & perms::owner_read) != perms::none ? 'r' : '-');
    std::cout << ((p & perms::owner_write) != perms::none ? 'w' : '-');
    std::cout << ((p & perms::owner_exec) != perms::none ? 'x' : '-');
    std::cout << ((p & perms::group_read) != perms::none ? 'r' : '-');
    std::cout << ((p & perms::group_write) != perms::none ? 'w' : '-');
    std::cout << ((p & perms::group_exec) != perms::none ? 'x' : '-');
    std::cout << ((p & perms::others_read) != perms::none ? 'r' : '-');
    std::cout << ((p & perms::others_write) != perms::none ? 'w' : '-');
    std::cout << ((p & perms::others_exec) != perms::none ? 'x' : '-');
}

static Options parse_options(const vector<string>& tokens){
    Options lsoptions {}; // this should contain default values within the struct
    for (size_t i = 0; i < tokens.size(); i++){
        auto const& token = tokens[i];
        if (token == "ls"){
            continue;
        } 
        //this loop should NOT change path if we only have ls -a, or ls -l
        if (token == "-la"|| token == "-al"){
            lsoptions.hidden = true;
            lsoptions.long_format = true;
        } else if (token == "-a"){
            lsoptions.hidden = true;
        } else if (token == "-l"){
            lsoptions.long_format = true;
        } else {
            lsoptions.path = token;
            lsoptions.pathExists = fs::exists(token);
        }
    }
    
    return lsoptions;
}

int main(int argc, char* argv[]){
        std::vector<std::string> tokens;
        //argv contains char pointers,
        //need to turn char* argv into vector<char*>
        //we want to 
        for (int i =0; i<argc; ++i){
            //need to cast
            tokens.push_back(argv[i]);
        }

        ls(tokens);

        return EXIT_SUCCESS;
}