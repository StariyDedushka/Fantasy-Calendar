#ifndef CALENDARPRESENTER_H
#define CALENDARPRESENTER_H

#include <QObject>
#include <QDate>
#include "calendarsystem.h"
#include "customdatetime.h"
#include "calendarview.h"
#include "calendarscene.h"

struct CalendarDisplayData {
    QVector<CalendarItem*> items;
    QDate currentDate;
    QString monthYearHeader;
    bool isValid;
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
    void onSystemTimeChanged();

private slots:
    void handleViewResized(quint16 width, quint16 height);
    void handleItemClicked(AbstractItem* item);

private:
    void setupConnections();
    CalendarDisplayData generateCalendarData() const;
    void updateView(const CalendarDisplayData& data);
    void validateCurrentDate();

    CalendarSystem* m_system;
    CustomDateTime* m_globalTime;
    CalendarView* m_view;
    CalendarScene* m_scene;

    CustomDateTime m_currentDisplayDate;
};

#endif // CALENDARPRESENTER_H
