#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QFile>
#include <QtXml>
#include "customdatetime.h"

class Settings
{
    // Q_OBJECT

private:
    CustomDateTime *system;
    QVector<quint16> groupIds;
    QVector<QColor*> groupColors;
    QVector<QString*> days;
    QVector<QString*> months;
    QFile config;
    QXmlStreamReader reader;
    QXmlStreamWriter writer;

public:
    Settings();
};

#endif // SETTINGS_H
