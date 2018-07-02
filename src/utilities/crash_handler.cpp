#include "crash_handler.h"

bool DumpCallback(const wchar_t* _dump_dir, const wchar_t* _minidump_id, void* context,
                  EXCEPTION_POINTERS* exinfo, MDRawAssertionInfo* assertion, bool success)
{
  Q_UNUSED(context);
  Q_UNUSED(_dump_dir);
  Q_UNUSED(_minidump_id);
  Q_UNUSED(assertion);
  Q_UNUSED(exinfo);

  qDebug("BreakpadQt crash");

  /*
  NO STACK USE, NO HEAP USE THERE !!!
  Creating QString's, using qDebug, etc. - everything is crash-unfriendly.
  */
  return success;
}

void Breakpad::init(const QString &reportPath)
{
    if (m_exceptionHandler == nullptr)
    {
        std::wstring pathAsStr = (const wchar_t*)reportPath.utf16();
        m_exceptionHandler = new google_breakpad::ExceptionHandler(pathAsStr,0, DumpCallback,0, true);
    }
}


