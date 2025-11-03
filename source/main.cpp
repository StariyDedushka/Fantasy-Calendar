#include "include/mainwindow.h"

#include <QApplication>
#include "include/settingswindow.h"
#include "include/applicationcontext.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ApplicationContext context;
    context.initializeBasicSystems();
    SettingsWindow settingsWindow(context.settings());

    MainWindow w(context.calendarSystem(), context.globalTime(), context.settings());
    w.initialize();
    w.show();
    settingsWindow.show();
    return a.exec();
}
