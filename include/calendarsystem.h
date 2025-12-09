#ifndef TimeSystem_H
#define TimeSystem_H

#include <QObject>
#include "structs.h"
#include "global_logger.h"
#include <QtSql>

#define TABLE_DAYS "daysTotal"
#define TABLE_EVENTS "events"

class CalendarSystem
{
    // Q_OBJECT

signals:
    void systemChanged();

private:
    QVector<Month*> *m_months;
    QVector<DayOfWeek*> *m_days;

    quint32 m_secondsPerMinute = 60;
    quint32 m_minutesPerHour = 60;
    quint32 m_hoursPerDay = 24;

    quint32 m_daysInWeek = 0;
    quint32 m_monthsInYear = 0;

    QSqlDatabase m_db;
    QString m_dbName;

    void setupDatabase();

public:
    CalendarSystem();
    CalendarSystem(const CalendarSystem&) = delete;
    ~CalendarSystem();

    // База данных
    void setDatabase(const QString& name);
    QString databaseName();
    DayOfWeek fetchDay(const CustomDateTime& date);

    QVector<Event> fetchEvents(const CustomDateTime& date);
    quint32 fetchEventsCount();

    // Настройки времени
    quint32 secondsPerMinute() const { return m_secondsPerMinute; }
    quint32 minutesPerHour() const { return m_minutesPerHour; }
    quint32 hoursPerDay() const { return m_hoursPerDay; }

    // Настройки календаря
    quint32 daysInWeek() const { return m_days->size(); }
    quint32 monthsInYear() const { return m_months->size(); }
    // void setDaysOfWeek(QVector<DayOfWeek> *daysTotal) { m_days = daysTotal; }
    // void setMonths(QVector<Month*> months) { m_months = months; }

    bool setTimeSystem(quint32 secPerMin, quint32 minPerHour, quint32 hoursPerDay);

    // Валидация даты
    bool isValidDate(quint32 day, quint32 month, quint32 year) const;
    bool isValidTime(quint32 hour, quint32 minute, quint32 second) const;

    // Утилиты
    DayOfWeek* dayOfWeek(quint32 day) const;
    DayOfWeek* firstDayOfMonth(quint32 month, quint32 year) const;
    quint32 daysInMonth(quint32 month, quint32 year = 0) const;
    quint32 daysInYear(quint32 year = 0) const;
    quint32 weeksInMonth(quint32 month, quint32 year = 0) const;

    bool addMonth(const QString &name, quint32 id, quint32 daysTotal, quint32 place = 0);
    bool removeMonth(const QString &name);
    bool removeMonth(quint32 id);

    bool editMonth(const QString& name, quint32 newDays);
    bool editMonth(const QString& name, const QString& newName);
    bool editMonth(quint32 id, quint32 newDays);
    bool editMonth(quint32 id, const QString& newName);
    bool moveMonth(const QString& name, quint32 newPlace);
    bool moveMonth(quint32 id, quint32 newPlace);

    bool addDayOfWeek(const QString &name, quint32 id, quint32 place = 0);
    bool removeDayOfWeek(const QString &name);
    bool removeDayOfWeek(quint32 id);

    bool editDayOfWeek(const QString& dayName, const QString& newName);
    bool editDayOfWeek(quint32 id, const QString& newName);
    bool moveDayOfWeek(quint32 id, quint32 newPlace);
    bool moveDayOfWeek(const QString& dayName, quint32 newPlace);

};

#endif // TimeSystem_H
