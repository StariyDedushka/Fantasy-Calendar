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
// signal
signals:
    void appliedChanges();
public slots:
    bool loadSettings();
    bool writeSettings();
    void dpw_valueChanged(int days);
    void months_currentIndexChanged(const QString &month);
    void dpm_valueChanged(int days);
    void days_currentIndexChanged(const QString &day);
    void days_editTextChanged(const QString &newDay);
    void months_editTextChanged(const QString &newMonth);
    void secPerMin_valueChanged(int spm);
    void minPerHour_valueChanged(int mph);
    void hourPerDay_valueChanged(int hpd);
    void eventGroups_currentIndexChanged(const QString &group);
    void eventGroups_editTextChanged(const QString &newGroup);
    void colorSelected(QColor color);
    void configs_currentIndexChanged(QString &config);
    void configs_editTextChanged(const QString &newConfig);
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
    QMap<quint32, QString*> groups;
    QVector<QColor*> groupColors;
    QVector<Day*> *days;
    QVector<Month*> *months;
    QXmlStreamReader reader;
    QXmlStreamWriter writer;
    QVector<QString*> configs;
    QString currentConfig;

public:
    static Settings* getInstance();
    static void setGlobalTime(CustomDateTime *globalTime);
};

#endif // SETTINGS_H
