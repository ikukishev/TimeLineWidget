QT       += core gui widgets

TARGET = TimeLine
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17

SOURCES += \
    CTimeLineChannel.cpp \
    CTimeLineIndicator.cpp \
    CTimeLineTrack.cpp \
    CTimeLineView.cpp \
   ITimeLineTrackViev.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
    CTimeLineChannel.h \
    CTimeLineIndicator.h \
    CTimeLineTrack.h \
    CTimeLineView.h \
   ITimeLineTrackViev.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
