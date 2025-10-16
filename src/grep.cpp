#include "grep.h"
#include <glob.h>
#include <map>
#include <fstream>


void setCountOnly(Options& options){
    options.countOnly = true;
    options.format = Format::COUNT;
}

void setNoFileName(Options& options){
    options.noFileName = true;
    options.format = Format::NOFILENAME;
}

void setRecursive(Options& options){
    options.recursive = true;
}

void setFilesWithMatches(Options& options){
    options.fileMatching = true;
    options.format = Format::FILESMATCHING;
}

void recursiveFileSearch(Options& options){
    auto dirIter = RecursiveDirIter(options.searchPath);
    size_t numFiles = std::distance(dirIter, {});
    //reserve memory for the number of files
    options.globFiles.reserve(numFiles);
    
    for (const auto& entry : RecursiveDirIter(options.searchPath)){
        if (!entry.path().has_extension()){ continue;}

        //need to clean up dealing with executables
        if (entry.path().extension() == ".o"){ continue;}

        cout << "adding file: " << entry.path().string() << "\n";
        options.globFiles.emplace_back(entry.path());
    }
}

void findMatchingFiles(Options& options) {
    glob_t glob_result;

    memset(&glob_result, 0, sizeof(glob_t));

    int globSuccess = glob(options.grepArgs[1].c_str(), 0, nullptr, &glob_result);
     
    options.globFiles.reserve(glob_result.gl_pathc);

    if (globSuccess == 0) {
        for (size_t i = 0; i < glob_result.gl_pathc; ++i) {
            options.globFiles.emplace_back(glob_result.gl_pathv[i]);
        }
    }
    
    globfree(&glob_result);
}

Options handleArgs(vector<string>& tokens){
    //grep -r pattern doesn't need fileArg
    Options options {};
    
    for (const auto& token : tokens){
        if (token == "grep"){ continue;}

        auto handler = flag_handlers.find(token);

        if (handler != flag_handlers.end()){
            cout << "inside handler for: " << token << "\n";
            handler->second(options);
        } else {
            options.grepArgs.push_back(token);
        }
    }
    cout << "supposed pattern: " << options.grepArgs[0] << "\n";
    options.pattern = regex(options.grepArgs[0]);

    if (options.recursive){
        if (options.grepArgs.size() > 1){
            options.searchPath = options.grepArgs[1]; //initializing filepath
        } 
        //globFiles is a vector
        recursiveFileSearch(options);
    } else { //if not recursive, if size == 1 -> stdin
        if (options.grepArgs.size() == 1){
            options.readStdIn = true;
        } else { //not recursive and more than 1 grepArg, second arg will be fileGlob
            findMatchingFiles(options); //need to get the matchingFiles
        }
    }

    return options;
}

void matchingInput(Options& options, std::istream& inputStream){
    string line;
    while (getline(inputStream,line)){
        if (regex_search(line, options.pattern)){
            options.lineCount++;
            options.outputLines.emplace_back(line);
        }
    }
}

void matchingInput(Options& options, const FilePath& filePath){

    std::ifstream fileStream(filePath);
    if (!fileStream){ return;}

    string filename = filePath.filename().string();

    string line;

    bool fileMatched = false;

    while (getline(fileStream, line)){
        if (regex_search(line, options.pattern)){
            options.lineCount++;

            options.outputLines.push_back(line);

            if (!fileMatched){
                options.filesMatching.push_back(filename);
                fileMatched = true;
            }
            if (options.fileMatching){ return;}

        }
    }
}

void printCount(Options& options){
    cout << options.lineCount << "\n";
}

void printFiles(Options& options){
    for (const auto& file : options.filesMatching){
        cout << file << "\n";
    }
}

void printLine(Options& options){
    for (const auto& line : options.outputLines){
        cout << line << "\n";
    }
}
//this will be called once we have dealt with all the outputs, i.e we have the fileNames and lines to output
void format(Options& options){
    //now we should have all the proper flags set    
    switch (options.format){
        case Format::COUNT:
            printCount(options);
            break;
        case Format::FILESMATCHING:
            printFiles(options);
            break;
        case Format::NOFILENAME:
            printLine(options);
            break;
        default:
            printLine(options);
            break;
    }
}

//method for opening files, this should be after globbing is done, that method probabl;y cannot be changed much
void grep(Options& options){
    
    if (options.readStdIn){
        matchingInput(options, std::cin);
    } else if (!options.globFiles.empty()) {
        for (const auto& file : options.globFiles){
            std::ifstream fileStream(file);
            matchingInput(options, fileStream);
        }
    } else {
        cerr << "Error: no files or input specified \n";
    }
    format(options); //this will call print functions for display
}

int main(int argc, const char* argv[]){
    vector<string> tokens(argv,argv+argc);

    Options options = handleArgs(tokens);

    grep(options);

    return EXIT_SUCCESS;
}

