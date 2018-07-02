QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG += force_debug_info

win32-msvc* {
  QMAKE_CXXFLAGS_WARN_ON -= -W3
  QMAKE_CXXFLAGS_WARN_ON += -W4 -w44640
  QMAKE_CXXFLAGS_RELEASE += -O2 -MD
  QMAKE_LFLAGS_RELEASE = /INCREMENTAL:NO /DEBUG /MAP /OPT:REF
}
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(external/breakpad.pri)

SOURCES += \
        src/main.cpp \
    src/utilities/crash_handler.cpp

HEADERS += \
    src/utilities/crash_handler.h
