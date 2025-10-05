#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);

    calendar = new CalendarView();
    // connect(timer, &QTimer::timeout, this, &MainWindow::slot_rebuild);
    // connect(this, &MainWindow::signal_windowResized, calendar, &CalendarView::slot_windowResized);

    calendar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    calendar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->verticalLayout_3->addWidget(calendar);
    calendar->show();
    eventsWindow = new EventView();
    ui->verticalLayout_2->addWidget(eventsWindow);
    eventsWindow->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    // emit signal_windowResized(calendarWidth, calendarHeight);
}

void MainWindow::slot_rebuild()
{
}


// void MainWindow::resizeEvent(QResizeEvent *event)
// {
//     quint16 calendarWidth = calendar->width();
//     quint16 calendarHeight = calendar->height();
//     emit signal_windowResized(calendarWidth, calendarHeight);

//     // qDebug() << "Current QGraphicsView width:" << m_calendarWidth;;
//     // qDebug() << "Current QGraphicsView height:" << m_calendarHeight;
// }
