#include "include/settings.h"


Settings::Settings(CalendarSystem *system, CustomDateTime *globalTime, QObject *parent) :
    QObject(parent)
    , m_system(system)
    , m_globalTime(globalTime)
    , m_days(new QVector<Day*>())
    , m_months(new QVector<Month*>())
{
    loadSettings();
}


Settings::~Settings()
{
    delete m_days;
    delete m_months;
    // writeSettings();
}

bool Settings::loadSettings()
{
    quint16 spm = 0, mph = 0, hpd = 0;
    QFile file;
    file.setFileName(QString("../config_%1").arg(m_currentConfig));

    QXmlStreamReader reader(&file);
    while(!reader.atEnd())
    {
        QXmlStreamReader::TokenType token = reader.readNext();

        switch(token)
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
            QString elementName = reader.name().toString();
            qDebug() << "Xml element started:" << elementName << reader.namespaceUri();

            if(elementName == "seconds per minute")
            {
                spm = reader.readElementText().toUInt();
                break;
            }

            if(elementName == "minutes per hour")
            {
                mph = reader.readElementText().toUInt();
                break;
            }

            if(elementName == "hours per day")
            {
                hpd = reader.readElementText().toUInt();
                break;
            }
            if(elementName == "m_days of week")
            {
                reader.readNext();
                while(!reader.isEndElement())
                {
                    if(reader.readElementText() == "day")
                    {
                        reader.readNext();
                        Day *day = new Day();
                        day->name = reader.readElementText();
                        reader.readNext();
                        day->id = reader.readElementText().toUInt();
                        m_days->append(std::move(day));
                    }
                    reader.readNext();
                }
            }
        }
}
    m_system->setTimem_system(spm, mph, hpd);
    file.close();
    return true;
}


bool Settings::writeSettings()
{

    QFile file;
    QXmlStreamWriter writer(&file);
    file.setFileName(QString("../config_%1").arg(m_currentConfig));
    writer.writeStartDocument();
//-----------------------------------------------------
    writer.writeStartElement("settings");

    writer.writeStartElement("time m_system");

    writer.writeTextElement("seconds per minute", QString::number(m_system->m_secondsPerMinute()));
    writer.writeTextElement("minutes per hour", QString::number(m_system->m_minutesPerHour()));
    writer.writeTextElement("hours per day", QString::number(m_system->m_hoursPerDay()));

    writer.writeStartElement("m_days of week");
    for(Day *day : *m_days)
    {
        writer.writeStartElement("day");
        writer.writeTextElement("day name", day->name);
        writer.writeTextElement("day id", QString::number(day->id));
        writer.writeEndElement();
    }
    writer.writeEndElement();

    writer.writeStartElement("m_months");
    for(Month *month : *m_months)
    {
        writer.writeStartElement("month");
        writer.writeTextElement("month name", month->name);
        writer.writeTextElement("month id", QString::number(month->id));
        writer.writeEndElement();
    }
    writer.writeEndElement();

    writer.writeEndElement();
//-----------------------------------------------
    writer.writeStartElement("event m_groups");

    for(EventGroup *group : m_groups)
    {
        writer.writeTextElement("group", group->name);
        writer.writeAttribute("id", QString::number(group->id));
    }

    writer.writeEndElement();

    writer.writeEndElement();

    file.close();

    return true;
}

void Settings::setGlobalTime(CustomDateTime *globalTime)
{
    this->globalTime = globalTime;
}
// quint16 Settings::countFiles()
// {
//     QDir saveDir("../m_configs");
//     QFileInfoList list = saveDir.entryInfoList();
//     for(int i = 0; i < m_configs.size(); i++)
//     {

//     }
// }


void Settings::dpm_valueChanged(int m_days, const QString &month)
{

}

void Settings::days_editTextChanged(quint16 id, const QString &newName)
{

}

void Settings::months_editTextChanged(quint16 id, const QString &newName)
{

}

void Settings::secPerMin_valueChanged(int spm)
{

}

void Settings::minPerHour_valueChanged(int mph)
{

}

void Settings::hourPerDay_valueChanged(int hpd)
{

}

void Settings::eventGroups_currentIndexChanged(quint16 id, const QString &group)
{

}

void Settings::eventGroups_editTextChanged(quint16 id, const QString &newGroup)
{

}

void Settings::colorSelected(QColor color)
{

}

void Settings::configs_currentIndexChanged(QString &config)
{

}

void Settings::configs_editTextChanged(quint16 id, const QString &newConfig)
{

}

void Settings::loadConfig_clicked(const QString& config)
{

}

void Settings::saveConfig_clicked(const QString& config)
{

}

void Settings::apply_clicked()
{

}

void Settings::cancel_clicked()
{

}
