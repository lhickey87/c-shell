#ifndef SHELL_H
#define SHELL_H

#include <vector>
#include <string>

void echo(std::vector<std::string>& tokens);
void ls(std::vector<std::string>& tokens);
void concat(std::vector<std::string>& tokens);
void pwdir();
void cd(std::vector<std::string>& tokens);
void cp(std::vector<std::string>& tokens);
void mkdir(std::vector<std::string>& tokens);

#endif