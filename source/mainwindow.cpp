#include "include/mainwindow.h"

MainWindow::MainWindow(CalendarSystem *system, CustomDateTime *globalTime, QWidget *parent)
    : QMainWindow(parent)
    , m_system(system)
    , m_globalTime(globalTime)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    // 1. Настраиваем правильную компоновку
    setupLayouts();

    // 2. Инициализация календаря
    calendarWindow = new CalendarView(m_system, m_globalTime);
    calendarWindow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    calendarWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Добавляем календарь в layout groupBox_calendar
    if (ui->groupBox_calendar->layout()) {
        ui->groupBox_calendar->layout()->addWidget(calendarWindow);
    }

    // 3. Инициализация events window
    eventsWindow = new EventView(m_system);
    eventsWindow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    eventsWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Добавляем eventsWindow в layout groupBox_events
    if (ui->groupBox_events->layout()) {
        ui->groupBox_events->layout()->addWidget(eventsWindow);
    }

    // 4. Настраиваем размеры
    ui->groupBox_events->setMinimumWidth(400);
    ui->groupBox_events->setMaximumWidth(800);
    ui->groupBox_events->setMinimumHeight(300);

    calendarWindow->show();
    eventsWindow->show();
}

void MainWindow::setupLayouts()
{
    // Убираем абсолютное позиционирование из centralwidget
    QLayout* centralLayout = ui->centralwidget->layout();
    if (!centralLayout) {
        // Создаем основной layout для centralwidget
        QHBoxLayout* mainLayout = new QHBoxLayout(ui->centralwidget);

        // Левая часть - календарь
        mainLayout->addWidget(ui->groupBox_calendar);

        // Правая часть - вертикальный layout для событий и управления временем
        QVBoxLayout* rightLayout = new QVBoxLayout();
        rightLayout->addWidget(ui->groupBox_events);
        rightLayout->addWidget(ui->groupBox_timeControl);

        mainLayout->addLayout(rightLayout);

        // Настраиваем пропорции
        mainLayout->setStretchFactor(ui->groupBox_calendar, 2);    // Календарь занимает 2/3
        mainLayout->setStretchFactor(rightLayout, 1);              // Правая часть 1/3
    }

    // Правильно настраиваем layout для groupBox_calendar
    setupCalendarLayout();

    // Убеждаемся, что у groupBox_events есть layout
    if (!ui->groupBox_events->layout()) {
        QVBoxLayout* eventsLayout = new QVBoxLayout(ui->groupBox_events);
        eventsLayout->setContentsMargins(2, 2, 2, 2);
    }
}

void MainWindow::setupCalendarLayout()
{
    // Если layout уже существует, не трогаем его структуру
    if (!ui->groupBox_calendar->layout()) {
        // Создаем вертикальный layout для календаря
        QVBoxLayout* calendarLayout = new QVBoxLayout(ui->groupBox_calendar);

        // Создаем горизонтальный layout для кнопок навигации
        QHBoxLayout* navLayout = new QHBoxLayout();

        // Добавляем кнопки в правильном порядке
        if (ui->btn_dayPrev_top) {
            navLayout->addWidget(ui->btn_dayPrev_top);
        }
        if (ui->btn_day_now) {
            navLayout->addWidget(ui->btn_day_now);
        }
        if (ui->btn_dayNext_top) {
            navLayout->addWidget(ui->btn_dayNext_top);
        }

        // Добавляем растяжку чтобы кнопки были слева
        navLayout->addStretch();

        // Добавляем навигацию сверху, а потом будет календарь
        calendarLayout->addLayout(navLayout);

        // Календарь добавится позже в конструкторе
    } else {
        // Если layout уже существует, проверяем его структуру
        QVBoxLayout* calendarLayout = qobject_cast<QVBoxLayout*>(ui->groupBox_calendar->layout());
        if (calendarLayout) {
            // Проверяем, есть ли уже кнопки в layout
            bool hasButtons = false;
            for (int i = 0; i < calendarLayout->count(); ++i) {
                QLayoutItem* item = calendarLayout->itemAt(i);
                if (item && item->layout() && item->layout()->count() > 0) {
                    hasButtons = true;
                    break;
                }
            }

            // Если кнопок нет, добавляем их
            if (!hasButtons) {
                QHBoxLayout* navLayout = new QHBoxLayout();

                if (ui->btn_dayPrev_top) {
                    navLayout->addWidget(ui->btn_dayPrev_top);
                }
                if (ui->btn_day_now) {
                    navLayout->addWidget(ui->btn_day_now);
                }
                if (ui->btn_dayNext_top) {
                    navLayout->addWidget(ui->btn_dayNext_top);
                }

                navLayout->addStretch();
                calendarLayout->insertLayout(0, navLayout); // Добавляем навигацию в начало
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    // emit signal_windowResized(calendarWidth, calendarHeight);
}



void MainWindow::on_btn_monthPrev_top_clicked()
{

}


void MainWindow::on_btn_monthNext_top_clicked()
{

}


void MainWindow::on_btn_dayPrev_top_clicked()
{

}


void MainWindow::on_btn_dayNext_top_clicked()
{

}


void MainWindow::on_btn_day_now_clicked()
{

}


void MainWindow::on_dateEdit_editingFinished()
{

}


void MainWindow::on_timeEdit_hours_valueChanged(int arg1)
{

}


void MainWindow::on_timeEdit_minutes_valueChanged(int arg1)
{

}


void MainWindow::on_btn_dayPrev_clicked()
{

}


void MainWindow::on_btn_dayNext_clicked()
{

}

