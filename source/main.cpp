#include "include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // CalendarPainter::connect(&calendar, &CalendarPainter::signal_rebuild, &w, &MainWindow::slot_rebuild);

    w.initialize();
    w.show();
    return a.exec();
}
