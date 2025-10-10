#ifndef SHELL_H
#define SHELL_H

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using FilePath = fs::path;

void cd(const std::vector<std::string>& tokens);
void mkdir(const std::vector<std::string>& tokens);
void rm(const std::vector<std::string>& tokens);

#endif