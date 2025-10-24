#include "include/mainwindow.h"

#include <QApplication>
#include "include/calendarsystem.h"
#include "include/settingswindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CalendarSystem *system = CalendarSystem::getInstance();
    SettingsWindow settings;
    system->setTimeSystem(60, 60, 24); // Стандартное время

    MainWindow w(system);
    w.initialize();
    w.show();
    return a.exec();
}
