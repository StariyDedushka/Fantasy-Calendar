#include "include/settings.h"

Settings* Settings::instance_ptr = nullptr;

Settings* Settings::getInstance()
{
    if(instance_ptr == nullptr)
        instance_ptr = new Settings();
    return instance_ptr;
}

bool Settings::loadSettings()
{
    return true;
}


bool Settings::writeSettings()
{

    QFile file;
    file.setFileName(QString("../config_%1").arg(currentConfig));
    writer.writeStartDocument();
//-----------------------------------------------------
    writer.writeStartElement("settings");

    writer.writeStartElement("time system");
    writer.writeTextElement("days per week", QString::number(system->daysPerWeek()));
    writer.writeTextElement("days per month", QString::number(system->daysPerMonth()));
    writer.writeTextElement("days per year", QString(system->daysPerYear()));
    writer.writeTextElement("months per year", QString::number(system->monthsPerYear()));

    writer.writeTextElement("seconds per minute", QString::number(system->secondsPerMinute()));
    writer.writeTextElement("minutes per hour", QString::number(system->minutesPerHour()));
    writer.writeTextElement("hours per day", QString::number(system->hoursPerDay()));

    for(QString *day : days)
    {
        writer.writeTextElement("day name", *day);
    }

    for(QString *month : months)
    {
        writer.writeTextElement("month name", *month);
    }

    writer.writeEndElement();
//-----------------------------------------------
    writer.writeStartElement("event groups");

    for(QString *name : groups)
    {
        writer.writeTextElement("group", *name);
        writer.writeAttribute("id", QString(groups.key(name)));
    }

    writer.writeEndElement();

    writer.writeEndElement();

    return true;
}

// quint16 Settings::countFiles()
// {
//     QDir saveDir("../configs");
//     QFileInfoList list = saveDir.entryInfoList();
//     for(int i = 0; i < configs.size(); i++)
//     {

//     }
// }
