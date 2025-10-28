#include "include/mainwindow.h"

#include <QApplication>
#include "include/calendarsystem.h"
#include "include/settingswindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CalendarSystem *system = CalendarSystem::getInstance();
    // CustomDateTime подходит для отображения времени каждого объекта, но тут его использую как глобальные часы
    // соответственно этот класс контролирует и глобальную дату
    CustomDateTime *globalTime = new CustomDateTime(system);
    // настройки подгружают параметры системы в CalendarSystem при загрузке конфигурации или включении приложения
    SettingsWindow settings;
    // глобальное время добавляется в настройки, чтобы они могли его выставлять
    settings.setGlobalTime(globalTime);
    system->addDayOfWeek("zhopa");
    system->addDayOfWeek("bebra");
    system->addDayOfWeek("goida");
    system->addMonth("1", 20);
    system->addMonth("3", 40);
    system->addMonth("8", 30);
    system->setTimeSystem(60, 60, 24); // Стандартное время

    globalTime->setDateTime(2, 2, 1000, 10, 5, 30);

    MainWindow w(system, globalTime);
    w.initialize();
    w.show();
    return a.exec();
}
