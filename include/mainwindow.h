#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include "abstractscene.h"
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
    void /*slot_*/rebuild();

public:
    MainWindow(CalendarSystem *system, QWidget *parent = nullptr);
    ~MainWindow();
    void initialize();

private:
    Ui::MainWindow *ui;
    CalendarView *calendar;
    EventView *eventsWindow;
    CalendarSystem *m_system;
    QTimer *timer;

    void setupLayouts();
    void setupCalendarLayout();


    // void resizeEvent(QResizeEvent *event);
};
#endif // MAINWINDOW_H
