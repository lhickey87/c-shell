#ifndef EXECUTABLES_H
#define EXECUTABLES_H

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using FilePath = fs::path;
using FileInfo = fs::file_status;
using FileSize = std::uintmax_t; //defined return type of fs::file_size
using FileType = fs::file_type;
using TokenIterator = std::vector<std::string>::const_iterator;
using DirectoryEntry = fs::directory_entry;
using DirectoryIter = fs::directory_iterator;

#endif