#ifndef SHELL_H
#define SHELL_H

#include <vector>
#include <string>

void echo(std::vector<std::string>& tokens);
void ls(std::vector<std::string>& tokens, size_t size);
void concat(std::vector<std::string>& tokens);
void pwdir();
void find(std::vector<std::string>& tokens);
void cd(std::vector<std::string>& tokens);
void mkdir(std::vector<std::string>& tokens);

#endif