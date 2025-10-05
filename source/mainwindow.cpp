#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    calendar = new CalendarView();
    calendar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    calendar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->verticalLayout_3->addWidget(calendar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    m_calendarWidth = calendar->width();
    m_calendarHeight = calendar->height();
    emit signal_windowResized(m_calendarWidth, m_calendarHeight);
}

void MainWindow::slot_rebuild(CalendarPainter *scene)
{
    calendar->setScene(scene);
    calendar->show();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_calendarWidth = calendar->width();
    m_calendarHeight = calendar->height();
    qDebug() << "Current QGraphicsView width:" << m_calendarWidth;;
    qDebug() << "Current QGraphicsView height:" << m_calendarHeight;
    emit signal_windowResized(m_calendarWidth, m_calendarHeight);
}
