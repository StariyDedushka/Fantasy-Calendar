#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QFile>
#include <QtXml>
#include "calendarsystem.h"
#include "customdatetime.h"
#include "common/calendarStructures.h"


class Settings : public QObject
{
    Q_OBJECT

signals:
    void appliedChanges();
public slots:
    bool loadSettings();
    bool writeSettings();
    void dpm_valueChanged(int days, const QString& month);
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

signals:
    void eventGroups_changed();

private:

    static Settings *instance_ptr;
    Settings();
    virtual ~Settings() override;
    CalendarSystem *system;
    CustomDateTime *globalTime;
    QVector<EventGroup*> groups;
    QMap<quint16, QColor*> groupColors;
    QVector<Day*> *days;
    QVector<Month*> *months;
    QVector<QString*> configs;
    QString currentConfig;

    quint16 daysPerMonth;
    quint16 secondsPerMinute;
    quint16 minutesPerHour;
    quint16 hoursPerDay;

public:
    static Settings* getInstance();
    void setGlobalTime(CustomDateTime *globalTime);
};

#endif // SETTINGS_H
