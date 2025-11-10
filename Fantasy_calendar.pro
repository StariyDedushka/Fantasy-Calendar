QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/eventpresenter.cpp \
    source/eventitem.cpp \
    source/calendarvisualstyle.cpp \
    source/eventitem.cpp \
    source/global_logger.cpp \
    source/logger.cpp \
    source/calendarpresenter.cpp \
    source/applicationcontext.cpp \
    source/settingswindow.cpp \
    source/settings.cpp \
    source/abstractscene.cpp \
    source/calendarscene.cpp \
    source/calendarsystem.cpp \
    source/customdatetime.cpp \
    source/eventcontainer.cpp \
    source/calendaritem.cpp \
    source/eventscene.cpp \
    source/eventview.cpp \
    source/calendarview.cpp \
    source/abstractitem.cpp \
    source/main.cpp \
    source/mainwindow.cpp

HEADERS += \
    include/abstractscene.h \
    include/applicationcontext.h \
    include/abstractitem.h \
    include/calendaritem.h \
    include/calendarpresenter.h \
    include/calendarscene.h \
    include/calendarsystem.h \
    include/calendarvisualstyle.h \
    include/customdatetime.h \
    include/eventcontainer.h \
    include/eventitem.h \
    include/eventpresenter.h \
    include/eventscene.h \
    include/eventview.h \
    include/eventvisualstyle.h \
    include/global_logger.h \
    include/logger.h \
    include/mainwindow.h \
    include/calendarview.h \
    include/settings.h  \
    include/common/calendarstructures.h \
    include/settingswindow.h

FORMS += \
    ui/mainwindow.ui \
    ui/settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    CMakeLists.txt
