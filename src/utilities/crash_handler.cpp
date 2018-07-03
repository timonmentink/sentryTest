#include "crash_handler.h"
#include <Qdir>
#include <string>
#include <QDebug>
#include <external/breakpad/src/common/windows/http_upload.h>

static bool DumpCallback(const wchar_t* _dump_dir, const wchar_t* _minidump_id, void* context,
                         EXCEPTION_POINTERS* exinfo, MDRawAssertionInfo* assertion, bool success)
{
    Q_UNUSED(context);
    Q_UNUSED(_dump_dir);
    Q_UNUSED(_minidump_id);
    Q_UNUSED(assertion);
    Q_UNUSED(exinfo);

    return success;
}

void Breakpad::init(const QString &reportPath)
{
    m_reportPath = reportPath;
    if (m_exceptionHandler == nullptr)
    {
        m_exceptionHandler = new google_breakpad::ExceptionHandler(m_reportPath.toStdWString(),0, DumpCallback,0, true);
    }
}

void Breakpad::sendDumps()
{


    if(!m_reportPath.isEmpty())
    {
        QDir dumpDir(m_reportPath);
        dumpDir.setNameFilters(QStringList()<<"*.dmp");
        QStringList dumpFiles = dumpDir.entryList();

        for (QString dmpFileName : dumpFiles)
        {
            // Add additional arguments for Sentry
            std::map<std::wstring, std::wstring> parameters;
            std::map<std::wstring, std::wstring> files;

            files[QString("upload_file_minidump").toStdWString()] = QString(m_reportPath + "/" + dmpFileName).toStdWString();

            int timeout = 1000;

            std::wstring returnBody;
            int returnCode = 0;

            google_breakpad::HTTPUpload::SendRequest(
                        m_uploadUrl.toStdWString(),
                        parameters,
                        files,
                        &timeout,
                        &returnBody,
                        &returnCode);
            if (returnCode == 200)
            {
                QFile::remove((QString(m_reportPath + "/" + dmpFileName));
            }
        }
    }

}
