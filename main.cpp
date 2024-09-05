#include <QApplication>
#include <QProcess>
#include <QDebug>
#include <QClipboard>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>



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

void copyTextToClipboard(const QString &text) {
    QApplication::clipboard()->setText(text);
}

// this function is for getting the path to all files in the given directory with the specified type 
std::vector<std::string> getFilesByType(const std::string& dirPath, const std::string& fileType) {
    std::vector<std::string> fileNames;
    std::filesystem::path directory(dirPath);

    // if the directory exists
    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) {
        std::cerr << "Error accessing the directory" << dirPath << std::endl;
        return fileNames;  // return empty 
    }


    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().extension() == fileType) {
                fileNames.push_back(entry.path().filename().string()); 
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing the directory: " << e.what() << std::endl;
    }

    return fileNames;
}


int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QProcess process;
    QString command;
// for windows 
#if defined(Q_OS_WIN)
    command = "cd";  
#else
    command = "pwd";  // for unix like systems
#endif

    // start the process
    process.start(command);


    if (!process.waitForFinished()) {
        qDebug() << "failed to execute command:" << process.errorString();
        return -1;
    }

    // read the output witch is the current directory . use trimmed to remove \n and stuff 
    QString output = process.readAllStandardOutput().trimmed();  
    
    std::cout <<output.toStdString() << std::endl;
    std::string dirPath = output.toStdString();
    // what we will put in clipboard at the end of program 
    std::string clipboard;
    //------------------------------------------------
    if (argc <= 1){
        std::cerr<<"you need to specify extensions of the files you want"<<std::endl;;
        return EXIT_FAILURE;
    }
    
    // reading the file types that user want 
    for (int i=1;i<argc;i++){
        std::string extension = std::string(argv[i]);
        // add '.' to extension specified by user if it doesn't have one  
        if (extension.at(0)!='.'){
            extension = "." + extension;
        }
        //get the list of all the files with that extension
        std::vector<std::string> filesWithThisExtension = getFilesByType(dirPath,extension);
        if (filesWithThisExtension.empty()){continue;}
        for (std::string &file : filesWithThisExtension){
            clipboard += file + ":\n\n\n";
            clipboard += readFileContent(dirPath+"/"+file) + "\n\n\n";
        }
    }
    QString copyClipboard = QString::fromStdString(clipboard); 
     QApplication::clipboard()->setText(QString::fromStdString(clipboard));
    app.processEvents();
    return 0;
}

