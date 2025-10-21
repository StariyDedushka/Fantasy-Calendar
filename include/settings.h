#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QFile>
#include <QtXml>
#include "calendarsystem.h"


class Settings : public QObject
{
    Q_OBJECT

signals:
    void appliedChanges();
public slots:

private:
    static Settings *instance_ptr;
    // Settings();
    CalendarSystem *system;
    QMap<quint32, QString*> groups;
    QVector<QColor*> groupColors;
    QVector<QString*> days;
    QVector<QString*> months;
    // QVector<QFile*> configs;
    QXmlStreamReader reader;
    QXmlStreamWriter writer;
    bool loadSettings();
    bool writeSettings();
    // quint16 countFiles();
    QVector<QString*> configs;
    QString currentConfig;

public:
    Settings* getInstance();
};

#endif // SETTINGS_H
