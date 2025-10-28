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
