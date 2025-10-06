#include "builtins.h"
#include <filesystem>
#include <iostream>
#include <utility>

using namespace std;
namespace fs = std::filesystem;

struct Options {
    bool r_flag = false;
    bool f_flag = false;
    vector<string> paths = {"."};
};

Options handle_tokens(const vector<string>& tokens);


void rm(const std::vector<std::string>& tokens) {
    Options opts = handle_tokens(tokens);

    if (opts.paths.empty()) {
        return; 
    }

    for (const auto& path_str : opts.paths) {
        fs::path p = path_str;
        std::error_code ec;

        if (!fs::exists(p) && opts.f_flag) {
            continue; 
        }

        if (!fs::exists(p)) {
            if (!opts.f_flag) { 
                std::cerr << "rm: cannot remove '" << p.string() << "': No such file or directory\n";
            }
            continue;
        }

        if (fs::is_directory(p)) {
            if (opts.r_flag) {
                try {
                    fs::remove_all(p);
                } catch (const fs::filesystem_error& e) {
                    if (!opts.f_flag) {
                        std::cerr << "rm: error removing directory '" << p.string() << "': " << e.what() << "\n";
                    }
                }
            } else {
                std::cerr << "rm: cannot remove '" << p.string() << "': Is a directory\n";
            }
        } 
        else { 
            if (!fs::remove(p, ec)) {
                if (ec && !opts.f_flag) {
                    std::cerr << "rm: error removing '" << p.string() << "': " << ec.message() << "\n";
                }
            }
        }
    }
}

Options handle_tokens(const vector<string>& tokens){

    Options options {};
    cout << "Initialized path is: " << options.paths.at(0) << "\n";
    std::vector<std::string> found_paths;
    //how do we handle the paths now?
    for (auto const& token: tokens){

        if (token == "-rf"){
            options.f_flag = true;
            options.r_flag = true;
        } else if (token == "-r"){
            options.r_flag = true;
        } else if (token == "-f"){
            options.f_flag = true;
        } else {
            //assuming it must then be a path argument
            //now we need to create a new path's vector, then call the move assignment
            found_paths.push_back(token);
        }

    }

    options.paths = std::move(found_paths);
    return options; 
}