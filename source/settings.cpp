#include "include/settings.h"

Settings* Settings::instance_ptr = nullptr;

Settings* Settings::getInstance()
{
    if(instance_ptr == nullptr)
        instance_ptr = new Settings();
    return instance_ptr;
}

Settings::Settings()
{
    loadSettings();
}

Settings::~Settings()
{
    // writeSettings();
}

bool Settings::loadSettings()
{
    quint16 spm, mph, hpd;
    QFile file;
    file.setFileName(QString("../config_%1").arg(currentConfig));
    while(!reader.atEnd())
    {
        reader.readNext();
        switch(reader.tokenType())
        {
        case QXmlStreamReader::StartDocument:
            qDebug() << "Xml document started";
            break;
        //-------------------------------------------
        case QXmlStreamReader::EndDocument:
            qDebug() << "Xml document ended";
            break;
        //-------------------------------------------
        case QXmlStreamReader::StartElement:
            qDebug() << "Xml element started:" << reader.name() << reader.namespaceUri();

            if(reader.name() == "seconds per minute")
            {
                spm = reader.readElementText().toUInt();
                break;
            }

            if(reader.name() == "minutes per hour")
            {
                mph = reader.readElementText().toUInt();
                break;
            }

            if(reader.name() == "hours per day")
            {
                hpd = reader.readElementText().toUInt();
                break;
            }
        }
}
    system->setTimeSystem(spm, mph, hpd);
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

    writer.writeTextElement("seconds per minute", QString::number(system->secondsPerMinute()));
    writer.writeTextElement("minutes per hour", QString::number(system->minutesPerHour()));
    writer.writeTextElement("hours per day", QString::number(system->hoursPerDay()));


    for(Day *day : *days)
    {
        writer.writeTextElement("day name", day->name);
        writer.writeTextElement("day id", QString::number(day->id));
    }

    for(Month *month : *months)
    {
        writer.writeTextElement("month name", month->name);
        writer.writeTextElement("month id", QString::number(month->id));
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

void Settings::setGlobalTime(CustomDateTime *globalTime)
{
    globalTime = globalTime;
}
// quint16 Settings::countFiles()
// {
//     QDir saveDir("../configs");
//     QFileInfoList list = saveDir.entryInfoList();
//     for(int i = 0; i < configs.size(); i++)
//     {

//     }
// }
