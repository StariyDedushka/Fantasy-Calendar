#include "include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CalendarPainter calendar;

    CalendarPainter::connect(&calendar, &CalendarPainter::signal_rebuild, &w, &MainWindow::slot_rebuild);
    CalendarPainter::connect(&w, &MainWindow::signal_windowResized, &calendar, &CalendarPainter::slot_windowChanged);

    calendar.initialize();
    w.initialize();
    w.show();
    return a.exec();
}
