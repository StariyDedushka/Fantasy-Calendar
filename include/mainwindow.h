#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include "AbstractScene.h"
#include "abstractitem.h"
#include "calendarview.h"
#include "eventview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

// signals:
//     void signal_windowResized(quint16 wWidth, quint16 wHeight);

private slots:
    void slot_rebuild();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialize();

private:
    Ui::MainWindow *ui;
    CalendarView *calendar;
    EventView *eventsWindow;
    QTimer *timer;


    // void resizeEvent(QResizeEvent *event);
};
#endif // MAINWINDOW_H
