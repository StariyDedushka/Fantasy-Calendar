#include "include/mainwindow.h"

#include <QApplication>
#include "include/calendarsystem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CalendarSystem *system = CalendarSystem::getInstance();
    system->setCalendarSystem(7, 30, 12, 365); // Стандартный календарь
    system->setTimeSystem(60, 60, 24); // Стандартное время

    MainWindow w(system);
    w.initialize();
    w.show();
    return a.exec();
}
