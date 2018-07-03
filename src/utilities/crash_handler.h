#ifndef CRASH_HANDLER_H
#define CRASH_HANDLER_H
#include <QString>
#include <Qurl>
#include <external/breakpad/src/client/windows/handler/exception_handler.h>

class Breakpad {
 public:
  static Breakpad& Instance() {
    // Since it's a static variable, if the class has already been created,
    // it won't be created again.
    // And it **is** thread-safe in C++11.
    static Breakpad breakpadInstance;

    // Return a reference to our instance.
    return breakpadInstance;
  }

  // delete copy and move constructors and assign operators
  Breakpad(Breakpad const&) = delete;             // Copy construct
  Breakpad(Breakpad&&) = delete;                  // Move construct
  Breakpad& operator=(Breakpad const&) = delete;  // Copy assign
  Breakpad& operator=(Breakpad &&) = delete;      // Move assign

  // Any other public methods.
  void init(const QString& reportPath);
  void setUploadUrl(const QString &uploadUrl) {m_uploadUrl = uploadUrl;}
  void sendDumps();

 protected:
  Breakpad() {
    // Constructor code goes here.
  }

  ~Breakpad() {
    // Destructor code goes here.
  }

private:
  google_breakpad::ExceptionHandler* m_exceptionHandler = nullptr;
  QString m_reportPath;
  QString m_uploadUrl;
};

#endif //CRASH_HANDLER_H
