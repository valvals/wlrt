QT += core gui widgets

RC_FILE = recource.rc
TARGET = WinLibRadTran
CONFIG += c++11

SOURCES += \
    libradtran/libradtran_ui.cpp \
    libradtran/libradtran_wrapper.cpp \
    main.cpp \
    message_reporter.cpp \
    pdf_util.cpp \
    qrc_files_restorer.cpp

HEADERS += \
    libradtran/libradtran_ui.h \
    libradtran/libradtran_wrapper.h \
    message_reporter.h \
    pdf_util.h \
    qrc_files_restorer.h \
    version.h

FORMS += \
    libradtran/libradtran_ui.ui

RESOURCES += \
    res.qrc
