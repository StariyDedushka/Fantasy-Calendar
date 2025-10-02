#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , painter(new CalendarPainter)
{
    ui->setupUi(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete painter;
}

void MainWindow::initialize()
{
    m_calendarWidth = ui->graphicsView->width();
    m_calendarHeight = ui->graphicsView->height();
    emit signal_windowResized(m_calendarWidth, m_calendarHeight);
}

void MainWindow::slot_rebuild(CalendarPainter *scene)
{
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_calendarWidth = ui->graphicsView->width();
    m_calendarHeight = ui->graphicsView->height();
    qDebug() << "Current QGraphicsView width:" << m_calendarWidth;;
    qDebug() << "Current QGraphicsView height:" << m_calendarHeight;
    emit signal_windowResized(m_calendarWidth, m_calendarHeight);
}
