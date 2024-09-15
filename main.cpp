#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "./clip/clip.h"


std::string readFileContent(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Error: could not open file " << filePath << std::endl;
        return ""; 
    }

    std::string content, line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    file.close();
    return content;
}

// this function is for getting the path to all files in the given directory with the specified type 
std::vector<std::string> getFilesByTypeRecursive(const std::string& dirPath, const std::string& fileType) {
    std::vector<std::string> filePaths;
    std::filesystem::path directory(dirPath);

    // check directory validity
    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) {
        std::cerr << "Error accessing the directory: " << dirPath << std::endl;
        return filePaths;
    }

    // recursive file search
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().extension() == fileType) {
                // Compute relative path from the given directory
                std::filesystem::path relativePath = std::filesystem::relative(entry.path(), directory);
                filePaths.push_back(relativePath.string());  
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Directory access error: " << e.what() << std::endl;
    }

    return filePaths;
}

std::vector<std::string> getFilesByType(const std::string& dirPath, const std::string& fileType) {
    std::vector<std::string> filePaths;
    std::filesystem::path directory(dirPath);

    // check directory validity
    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) {
        std::cerr << "Error accessing the directory: " << dirPath << std::endl;
        return filePaths;
    }

    // non-recursive file search
    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().extension() == fileType) {
                // Compute relative path from the given directory
                std::filesystem::path relativePath = std::filesystem::relative(entry.path(), directory);
                filePaths.push_back(relativePath.string());  
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Directory access error: " << e.what() << std::endl;
    }

    return filePaths;
}
int main(int argc, char *argv[]){
    std::string dirPath ;
    try {
        std::filesystem::path currentPath = std::filesystem::current_path();
        dirPath = currentPath;

    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error getting the current directory: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    // what we will put in clipboard at the end of program 
    std::string clipboard;
    //------------------------------------------------
    if (argc <= 1){
        std::cerr<<"you need to specify extensions of the files you want"<<std::endl;;
        return EXIT_FAILURE;
    }
    // application manual by reading the second element of argv (argv2) 
    std::string argv2 = std::string(argv[1]);
    if(argv2 == "--help" || argv2 == "-help" || argv2 == "--h" || argv2 == "-h"){
        std::cout << "Usage: ./LAC [options] <file extensions>\n\n"
          << "Options:\n"
          << "  -r          Apply recursive search to file extensions listed after this flag.\n\n"
          << "Description:\n"
          << "  LLM-Assist-Clip (LAC) is a utility designed to simplify the process of preparing and\n"
          << "  transferring project files to large language models (LLMs). It automates the task of\n"
          << "  copying file contents to your clipboard in a structured format, making it easy for AI\n"
          << "  to parse and understand. Useful for developers working with AI platforms that require\n"
          << "  manual input of code snippets or entire files.\n\n"
          << "Examples:\n"
          << "  1. Search for .cpp and .h files non-recursively:\n"
          << "     ./LAC .cpp .h\n\n"
          << "  2. Search for .txt and .md files recursively:\n"
          << "     ./LAC -r .txt .md\n\n"
          << "  3. Search for all specified file types recursively:\n"
          << "     ./LAC -r .cpp .h .txt\n\n"
          << "External Libraries Used:\n"
          << "  - Clip: A cross-platform library used for clipboard operations.\n\n"
          << "For more information, visit the GitHub repository: https://github.com/iman-zamani/LLM-Assist-Clip\n";

        return 0;
    } 
    
    bool recursive = false;
    
    // reading the file types that user want 
    for (int i=1;i<argc;i++){
        std::string extension = std::string(argv[i]);
        // check to see where should we look recursively 
        if (extension == "-r"){
            recursive = true;
            continue;
        }
        // add '.' to extension specified by user if it doesn't have one  
        if (extension.at(0)!='.'){
            extension = "." + extension;
        }
        //get the list of all the files with that extension
        std::vector<std::string> filesWithThisExtension;
        if (recursive) filesWithThisExtension = getFilesByTypeRecursive(dirPath,extension);
        else filesWithThisExtension = getFilesByType(dirPath,extension);
        if (filesWithThisExtension.empty()){continue;}
        for (std::string &file : filesWithThisExtension){
            clipboard += file + ":\n\n\n";
            clipboard += readFileContent(dirPath+"/"+file) + "\n\n\n";
        }
    }
    clip::set_text(clipboard);
    return 0;
}






