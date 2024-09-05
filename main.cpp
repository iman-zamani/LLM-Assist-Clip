#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QApplication>
#include <QClipboard>
#include <iostream>
#include <fstream>
#include <string>


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
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text, QClipboard::Clipboard);
    
    // for linux only
    clipboard->setText(text, QClipboard::Selection);
}



int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);

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

    // what we will put in clipboard at the end of program 
    std::string clipboard;
    // reading the file extensions that user want 
    for (int i=1;i<argc;i++){
        clipboard += std::string(argv[i]);
    }
    return 0;
}