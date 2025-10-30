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
    
    public slots"

public:
    MainWindow(CalendarSystem *system, CustomDateTime *globalTime, QWidget *parent = nullptr);
    ~MainWindow();
    void initialize();

private:
private slots:
    void on_btn_monthPrev_top_clicked();

    Ui::MainWindow *ui;
    CalendarView *calendar;
    EventView *eventsWindow;
    CalendarSystem *m_system;
    CustomDateTime *m_globalTime;

    void setupLayouts();
    void setupCalendarLayout();
    void setupMenu();
    void setupActions();


    // void resizeEvent(QResizeEvent *event);
    void on_btn_monthNext_top_clicked();
    void on_btn_dayPrev_top_clicked();
    void on_btn_dayNext_top_clicked();
    void on_btn_day_now_clicked();
    void on_dateEdit_editingFinished();
    void on_timeEdit_hours_valueChanged(int arg1);
    void on_timeEdit_minutes_valueChanged(int arg1);
    void on_btn_dayPrev_clicked();
    void on_btn_dayNext_clicked();
};
#endif // MAINWINDOW_H
