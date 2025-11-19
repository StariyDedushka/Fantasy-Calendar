#ifndef CALENDARPRESENTER_H
#define CALENDARPRESENTER_H

#include <QObject>
#include <QSize>
#include <QDebug>
#include <QVector>

#include "calendarsystem.h"
#include "customdatetime.h"
#include "calendarview.h"
#include "calendarvisualstyle.h"

// #include "common/calendarstructures.h"


class CalendarPresenter : public QObject
{
    Q_OBJECT

public:
    explicit CalendarPresenter(CalendarSystem* system,
                               CustomDateTime* globalTime,
                               CalendarView* view,
                               QObject* parent = nullptr);
    ~CalendarPresenter();

    void initialize();
    void refreshCalendar();

public slots:
    void onNextDay();
    void onPrevDay();
    void onNextMonth();
    void onPrevMonth();
    void onToday();
    void onDateSelected(const CustomDateTime& date);

    // Обработка внешних событий
    void onSystemChanged();
    void onSettingsChanged();
    void onEventsUpdated();

private slots:
    // Обработка сигналов от View
    void handleDateClicked(const CustomDateTime& date);
    void handleViewResized(const QSize& size);
    void handleItemClicked(CalendarItem* item);
    void handleWheelZoom(qreal factor);

private:
    void setupConnections();
    CalendarVisualData generateVisualData() const;
    void updateView(const CalendarVisualData& data);
    void validateCurrentDate();
    void calculateGridSize();
    QVector<CalendarDayData> generateMonthDays() const;
    QString generateHeaderText() const;
    QString generateWeekDaysHeader() const;
    // Методы для работы со стилями
    void applyVisualStyle();
    void updateColorsFromSettings();

    // Визуальные настройки
    QColor getDayColor(const CalendarDayData& dayData) const;
    QColor getTextColor(const CalendarDayData& dayData) const;
    QColor getBorderColor(const CalendarDayData& dayData) const;

    CalendarSystem* m_system;
    CustomDateTime* m_globalTime;
    CalendarView* m_view;
    // Визуальные настройки
    CalendarVisualStyle m_visualStyle;

    CustomDateTime m_currentDisplayDate;
    QSize m_viewSize;
    quint16 m_columns;
    quint16 m_rows;
    qreal m_zoomLevel;
};

#endif // CALENDARPRESENTER_H
