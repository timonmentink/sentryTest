#include "utilities/crash_handler.h"
#include <QCoreApplication>

int buggyFunc() {
    delete reinterpret_cast<QString*>(0xFEE1DEAD);
    return 0;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // We put the dumps in the user's home directory for this example:
       Breakpad::Instance().init(qApp->applicationDirPath());

       buggyFunc();


    return a.exec();
}
