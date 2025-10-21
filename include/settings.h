#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QFile>
#include <QtXml>
#include "customdatetime.h"

class Settings
{
    Q_OBJECT

private:
    CustomDateTime *system;

public:
    Settings();
};

#endif // SETTINGS_H
