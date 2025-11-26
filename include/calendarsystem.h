#ifndef TimeSystem_H
#define TimeSystem_H

#include <QObject>
#include "include/common/calendarstructures.h"
#include "global_logger.h"
#include <QtSql>

#define TABLE_DAYS "days"
#define TABLE_EVENTS "events"

class CalendarSystem
{
    // Q_OBJECT

signals:
    void systemChanged();

private:
    QVector<Month*> *m_months;
    QVector<DayOfWeek*> *m_days;

    quint16 m_secondsPerMinute = 60;
    quint16 m_minutesPerHour = 60;
    quint16 m_hoursPerDay = 24;

    quint16 m_daysInWeek = 0;
    quint16 m_monthsInYear = 0;

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
    DayOfWeek fetchDay(quint32 id);
    DayOfWeek fetchDay(const CustomDateTime& date);
    Event fetchEvent(quint32 id);
    Event fetchEvent(const CustomDateTime& date);

    // Настройки времени
    quint16 secondsPerMinute() const { return m_secondsPerMinute; }
    quint16 minutesPerHour() const { return m_minutesPerHour; }
    quint16 hoursPerDay() const { return m_hoursPerDay; }

    // Настройки календаря
    quint16 daysInWeek() const { return m_days->size(); }
    quint16 monthsInYear() const { return m_months->size(); }
    // void setDaysOfWeek(QVector<DayOfWeek> *days) { m_days = days; }
    // void setMonths(QVector<Month*> months) { m_months = months; }

    bool setTimeSystem(quint16 secPerMin, quint16 minPerHour, quint16 hoursPerDay);

    // Валидация даты
    bool isValidDate(quint16 day, quint16 month, quint32 year) const;

    // Утилиты
    DayOfWeek* dayOfWeek(quint16 day) const;
    DayOfWeek* firstDayOfMonth(quint16 month, quint32 year) const;
    quint16 daysInMonth(quint16 month, quint32 year = 0) const;
    quint32 daysInYear(quint32 year = 0) const;
    quint16 weeksInMonth(quint16 month, quint32 year = 0) const;

    bool addMonth(const QString &name, quint32 id, quint16 days, quint16 place = 0);
    bool removeMonth(const QString &name);
    bool removeMonth(quint16 id);

    bool editMonth(const QString& name, quint16 newDays);
    bool editMonth(const QString& name, const QString& newName);
    bool editMonth(quint16 id, quint16 newDays);
    bool editMonth(quint16 id, const QString& newName);
    bool moveMonth(const QString& name, quint16 newPlace);
    bool moveMonth(quint16 id, quint16 newPlace);

    bool addDayOfWeek(const QString &name, quint32 id, quint16 place = 0);
    bool removeDayOfWeek(const QString &name);
    bool removeDayOfWeek(quint32 id);

    bool editDayOfWeek(const QString& dayName, const QString& newName);
    bool editDayOfWeek(quint32 id, const QString& newName);
    bool moveDayOfWeek(quint32 id, quint16 newPlace);
    bool moveDayOfWeek(const QString& dayName, quint16 newPlace);

};

#endif // TimeSystem_H
