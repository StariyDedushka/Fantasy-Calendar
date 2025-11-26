#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QFile>
#include <QtXml>
#include "calendarsystem.h"
#include "customdatetime.h"
#include "common/calendarstructures.h"
#include <QRandomGenerator>


class Settings : public QObject
{
    Q_OBJECT

signals:
    void appliedChanges();
public slots:
    bool loadSettings();
    bool writeSettings();
    void dpm_valueChanged(int m_days, const QString& month);
    void days_editTextChanged(quint16 id, const QString &newName);
    void months_editTextChanged(quint16 id, const QString &newName);
    void secPerMin_valueChanged(int spm);
    void minPerHour_valueChanged(int mph);
    void hourPerDay_valueChanged(int hpd);
    void eventGroups_currentIndexChanged(quint16 id, const QString &group);
    void eventGroups_editTextChanged(quint16 id, const QString &newGroup);
    void colorSelected(QColor color);
    void configs_currentIndexChanged(QString &config);
    void configs_editTextChanged(quint16 id, const QString &newConfig);
    void loadConfig_clicked(const QString& config);
    void saveConfig_clicked(const QString& config);
    void apply_clicked();
    void cancel_clicked();
    void addDay_clicked();

signals:
    void eventGroups_changed();

private:

    CalendarSystem *m_system;
    CustomDateTime *m_globalTime;
    QVector<EventGroup*> m_groups;
    QMap<quint16, QColor*> groupColors;
    QVector<DayOfWeek*> *m_days;
    QVector<Month*> *m_months;
    QVector<QString*> m_configs;
    QString m_currentConfig;

    QSqlDatabase m_db;

    quint16 m_daysPerMonth;
    quint16 m_secondsPerMinute;
    quint16 m_minutesPerHour;
    quint16 m_hoursPerDay;

public:
    // Удаляем конструктор копирования и оператор присваивания
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
    Settings() = delete;

    Settings(CalendarSystem *system, CustomDateTime *globalTime, QObject *parent = nullptr);
    virtual ~Settings() override;
    void createDatabase();
};

#endif // SETTINGS_H
