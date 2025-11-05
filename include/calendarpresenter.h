#ifndef CALENDARPRESENTER_H
#define CALENDARPRESENTER_H

#include <QObject>
#include <QDate>
#include <QSize>
#include "calendarsystem.h"
#include "customdatetime.h"
#include "calendarview.h"
#include "calendarscene.h"
#include "calendaritem.h"

// Структуры данных для отображения
struct CalendarDayData {
    quint16 day;
    quint16 month;
    quint32 year;
    QString displayText;
    bool isEnabled;
    bool isCurrentDay;
    bool isToday;
    bool hasEvents;
    QColor backgroundColor;
    QColor textColor;
    QColor borderColor;
};

struct CalendarVisualData {
    QVector<CalendarDayData> days;
    QString headerText;
    QString weekDaysHeader;
    QSize gridSize; // columns x rows
    QSizeF cellSize;
};

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
    void onDateSelected(const QDate& date);

    // Обработка внешних событий
    void onSystemChanged();
    void onSettingsChanged();
    void onEventsUpdated();

private slots:
    // Обработка сигналов от View
    void handleDateClicked(const QDate& date);
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

    // Визуальные настройки
    QColor getDayColor(const CalendarDayData& dayData) const;
    QColor getTextColor(const CalendarDayData& dayData) const;
    QColor getBorderColor(const CalendarDayData& dayData) const;

    CalendarSystem* m_system;
    CustomDateTime* m_globalTime;
    CalendarView* m_view;

    QDate m_currentDisplayDate;
    QSize m_viewSize;
    quint16 m_columns;
    quint16 m_rows;
    qreal m_zoomLevel;
};

#endif // CALENDARPRESENTER_H
