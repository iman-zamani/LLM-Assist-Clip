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






