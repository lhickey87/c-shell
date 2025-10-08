#ifndef SHELL_H
#define SHELL_H

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

void echo(const std::vector<std::string>& tokens);
void ls(const std::vector<std::string>& tokens);
void concat(const std::vector<std::string>& tokens);
void find(std::vector<std::string>& tokens);
void cd(std::vector<std::string>& tokens);
void mkdir(std::vector<std::string>& tokens);
void rm(const std::vector<std::string>& tokens);

#endif