#include "executables.h"


using namespace std;

struct Options {
    string path = ".";
    bool hidden = false;
    bool long_format = false;
    bool pathExists = true;
};

using Permissions = fs::perms;
using DirectoryIter = fs::directory_iterator;

static Options handleTokens(const vector<string>& tokens);
void long_format(const DirectoryEntry& entry);
void print_perms(Permissions perms);


void ls(const vector<string>& tokens) {
    
    Options lsoptions = handleTokens(tokens);
    if (!lsoptions.pathExists){
        std::cout << "ls: " << lsoptions.path << ": No such file or directory \n";
        return; 
    } 

    const FilePath directory(lsoptions.path);

    if (!fs::is_directory(directory)) {
        std::cout << lsoptions.path << "\n";
        return; 
    }

    try {
        DirectoryIter di(directory);
       
        //di is a directory_iterator
        for (auto const& entry : di){
            
            const string name = entry.path().filename().string();

            if (lsoptions.long_format && lsoptions.hidden){

                long_format(entry); 

            } else if (lsoptions.long_format){
                if (name[0]== '.'){ continue;}

                long_format(entry); 
                
            } else {

                cout << name << "\n";

            }

        } 
    } catch (const fs::filesystem_error& e) {
        std::cerr << "ls: error accessing " << lsoptions.path << ": " << e.what() << "\n";
    }
}



void long_format(const DirectoryEntry& entry){
    const FilePath p = entry.path();
    try {

        fs::file_status status = fs::status(p);

        Permissions file_perms = status.permissions();

        print_perms(file_perms);

        cout << " " << entry.path().filename().string() << "\n";

    } catch (const fs::filesystem_error& e){

        cerr << "Error: " << e.what() << "\n";
        
    }
}

void print_perms(Permissions p) {
    cout << ((p & Permissions::owner_read) != Permissions::none ? 'r' : '-');
    cout << ((p & Permissions::owner_write) != Permissions::none ? 'w' : '-');
    cout << ((p & Permissions::owner_exec) != Permissions::none ? 'x' : '-');
    cout << ((p & Permissions::group_read) != Permissions::none ? 'r' : '-');
    cout << ((p & Permissions::group_write) != Permissions::none ? 'w' : '-');
    cout << ((p & Permissions::group_exec) != Permissions::none ? 'x' : '-');
    cout << ((p & Permissions::others_read) != Permissions::none ? 'r' : '-');
    cout << ((p & Permissions::others_write) != Permissions::none ? 'w' : '-');
    cout << ((p & Permissions::others_exec) != Permissions::none ? 'x' : '-');
}

static Options handleTokens(const vector<string>& tokens){
    Options lsoptions {}; // this should contain default values within the struct
    for (size_t i = 0; i < tokens.size(); i++){
        auto const& token = tokens[i];
        if (token == "ls"){
            continue;
        } 
        
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
        const vector<string> tokens(argv,argc+argv);
        
        ls(tokens);

        return EXIT_SUCCESS;
}