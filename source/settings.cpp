#include "include/settings.h"


Settings::Settings(CalendarSystem* system, CustomDateTime* globalTime, QObject *parent) :
    QObject(parent)
    , m_system(system)
    , m_globalTime(globalTime)
{
    loadSettings();
}


Settings::~Settings()
{
    // writeSettings();
    if(m_db.isOpen())
        m_db.close();
}

EventContainerData Settings::getContainer(quint32 id) const
{
    EventContainerData data;
    for(EventContainerData data : m_containers)
    {
        if(data.id == id)
        {
            LOG(INFO, logger, QString("Retrieved container with id %1").arg(id));
            return data;
        }
    }

    LOG(WARN, logger, QString("Couldn't retrieve container with id %1").arg(id));

    data.id = 0;
    data.displayText["name"] = "NULL";
    return data;
}

void Settings::createDatabase(const QString& newConfig)
{
    m_db.addDatabase("QSQLITE");
    QString name = newConfig;
    name.append(".db");
    m_db.setDatabaseName(name);
    m_db.open();

    QSqlQuery queryDaysTable("CREATE TABLE IF NOT EXISTS days("
                            "id int not null primary key,"
                            "date text,"
                            "weekdayid int not null);");

    QSqlQuery queryEventsTable("CREATE TABLE IF NOT EXISTS events("
                               "id int not null primary key,"
                               "dayid int not null,"
                               "groupid int not null);"
                               "time text,"
                               "name text,"
                               "contents text);");

    if(!queryDaysTable.exec() || !queryEventsTable.exec())
    {
        LOG(ERROR, logger, "Could not create a new database");
        m_db.close();
    }
}

bool Settings::loadSettings()
{
    quint16 spm = 0, mph = 0, hpd = 0;
    QFile file;
    file.setFileName(QString("../%1").arg(m_currentConfig.second));

    QXmlStreamReader reader(&file);
    while(!reader.atEnd())
    {
        QXmlStreamReader::TokenType token = reader.readNext();

        switch(token)
        {
        case QXmlStreamReader::StartDocument:
            LOG(INFO, logger, "Xml document reading started");
            break;
        //-------------------------------------------
        case QXmlStreamReader::EndDocument:
            LOG(INFO, logger, "Xml document reading ended");
            break;
        //-------------------------------------------
        case QXmlStreamReader::StartElement:
            QString elementName = reader.name().toString();
            qDebug() << "Xml element started:" << elementName << reader.namespaceUri();
            LOG(INFO, logger, QString("Reading Xml element: %1, namespace %2").arg(elementName).arg(reader.namespaceUri()));

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
            if(elementName == "days of week")
            {
                reader.readNext();
                while(!reader.isEndElement())
                {
                    if(reader.readElementText() == "day")
                    {
                        reader.readNext();
                        DayOfWeek day;
                        day.name = reader.readElementText();
                        reader.readNext();
                        day.id = reader.readElementText().toUInt();
                        m_days.append(day);
                        m_system->addDayOfWeek(day.name, day.id);
                    }
                    reader.readNext();
                }
            }
        }
}
    m_system->setTimeSystem(spm, mph, hpd);
    m_system->setDatabase(m_currentConfig.second);
    file.close();
    return true;
}


bool Settings::writeSettings()
{

    QFile file;
    QXmlStreamWriter writer(&file);
    file.setFileName(QString("../%1").arg(m_currentConfig.second));
    writer.writeStartDocument();
//-----------------------------------------------------
    writer.writeStartElement("settings");

    writer.writeStartElement("time system");

    writer.writeTextElement("seconds per minute", QString::number(m_system->secondsPerMinute()));
    writer.writeTextElement("minutes per hour", QString::number(m_system->minutesPerHour()));
    writer.writeTextElement("hours per day", QString::number(m_system->hoursPerDay()));

    writer.writeStartElement("days of week");
    for(DayOfWeek day : m_days)
    {
        writer.writeStartElement("day");
        writer.writeTextElement("day name", day.name);
        writer.writeTextElement("day id", QString::number(day.id));
        writer.writeEndElement();
    }
    writer.writeEndElement();

    writer.writeStartElement("months");
    for(Month month : m_months)
    {
        writer.writeStartElement("month");
        writer.writeTextElement("month name", month.name);
        writer.writeTextElement("month id", QString::number(month.id));
        writer.writeEndElement();
    }
    writer.writeEndElement();

    writer.writeEndElement();
//-----------------------------------------------
    writer.writeStartElement("event containers");

    for(EventContainerData container : m_containers)
    {
        writer.writeTextElement("container name", container.displayText["name"]);
        writer.writeAttribute("container id", QString::number(container.id));
    }

    writer.writeEndElement();

    writer.writeEndElement();

    file.close();

    return true;
}



void Settings::dpm_valueChanged(int m_days, const QString &month)
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

void Settings::eventGroups_currentIndexChanged(const QString &group)
{

}

void Settings::colorSelected(QColor color)
{

}

void Settings::configs_currentIndexChanged(const QString& config)
{
    m_currentConfig.second = config;
    LOG(INFO, logger, QString("The current config is now <%1>").arg(config));
}

void Settings::btn_removeConfig_clicked(const std::pair<int, QString>& config)
{
    QFile file;
    QString filename(m_configsPath);
    filename.append(config.second).append(".xml");

    if(file.remove(filename))
    {
        int uiIndex = config.first; // Сохраняем индекс из UI

        // Ищем и удаляем из вектора
        int foundIndex = -1;
        for(int i = 0; i < m_configs.size(); ++i)
        {
            if(m_configs[i].second == config.second)
            {
                foundIndex = i;
                break;
            }
        }

        if(foundIndex != -1)
        {
            LOG(INFO, logger, QString("Trying to remove pair: <%1>:<%2>").arg(foundIndex).arg(config.second));
            m_configs.remove(foundIndex);
        }
        else
        {
            LOG(WARN, logger, QString("Config <%1> not found in vector").arg(config.second));
        }

        LOG(INFO, logger, QString("Config <%1> removed successfully").arg(filename));

        // Отправляем индекс из UI для удаления из комбобокса
        emit configRemoved(uiIndex);
        return;
    }
    LOG(ERROR, logger, QString("Config <%1> could not be removed").arg(filename));
}


void Settings::loadConfig_clicked(const QString& config)
{

}

void Settings::btn_addConfig_clicked(const std::pair<int, QString>& config)
{
    QFile file;

    QString filename(m_configsPath);
    filename.append(config.second).append(".xml");
    file.setFileName(filename);
    if(file.open(QIODevice::WriteOnly))
    {
        m_configs.append(config);
        LOG(INFO, logger, QString("Config <%1> added succesfully").arg(filename));
        return;
    }
    LOG(ERROR, logger, QString("Config <%1> could not be added").arg(filename));

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

void Settings::addDay_clicked()
{
}
