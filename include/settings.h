#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QFile>
#include <QtXml>
#include "calendarsystem.h"
#include "common/calendarStructures.h"


class Settings : public QObject
{
    Q_OBJECT

signals:
    void appliedChanges();
public slots:

private:
    static Settings *instance_ptr;
    Settings() { }
    CalendarSystem *system;
    QMap<quint32, QString*> groups;
    QVector<QColor*> groupColors;
    QVector<Day*> *days;
    QVector<Month*> *months;
    QXmlStreamReader reader;
    QXmlStreamWriter writer;
    bool loadSettings();
    bool writeSettings();
    QVector<QString*> configs;
    QString currentConfig;

public:
    static Settings* getInstance();
};

#endif // SETTINGS_H
