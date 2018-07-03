#include "utilities/crash_handler.h"
#include <QCoreApplication>
#include <QDir>

void crash() { volatile int* a = (int*)(NULL); *a = 1; }



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString crashDir = qApp->applicationDirPath() + "/crashes";

   // We put the dumps in the user's home directory for this example:
    Breakpad::Instance().init(crashDir);
    Breakpad::Instance().setUploadUrl("https://sentry.io/api/1235621/minidump?sentry_key=08530653215141a8b0a1fe94c19ac16c");
    Breakpad::Instance().sendDumps();

    //crash();


    return a.exec();
}
