#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "calendarpainter.h"
#include "calendaritem.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void signal_windowResized(quint32 wWidth, quint32 wHeight);

public slots:
    void slot_rebuild(CalendarPainter *scene);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialize();

private:
    Ui::MainWindow *ui;
    CalendarPainter *painter;
    quint32 m_calendarWidth;
    quint32 m_calendarHeight;


    void resizeEvent(QResizeEvent *event);
};
#endif // MAINWINDOW_H
