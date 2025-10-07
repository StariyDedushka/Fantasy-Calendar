QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/calendarpainter.cpp \
    source/calendaritem.cpp \
    source/abstractpainter.cpp \
    source/eventpainter.cpp \
    source/eventview.cpp \
    source/calendarview.cpp \
    source/abstractitem.cpp \
    source/main.cpp \
    source/mainwindow.cpp \
    source/calendarevent.cpp \

HEADERS += \
    include/abstractpainter.h \
    include/calendarevent.h \
    include/abstractitem.h \
    include/calendaritem.h \
    include/calendarpainter.h \
    include/eventpainter.h \
    include/eventview.h \
    include/mainwindow.h \
    include/structs.h \
    include/calendarview.h

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
