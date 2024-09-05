#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
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
        qDebug() << "failed to execute the command:" << process.errorString();
        return -1;
    }

    // read the output witch is the current directory . use trimmed to remove \n and stuff 
    QString output = process.readAllStandardOutput().trimmed();  

    std::cout <<output.toStdString() << std::endl;

    return 0;
}