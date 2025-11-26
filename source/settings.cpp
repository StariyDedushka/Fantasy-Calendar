#include "include/settings.h"


Settings::Settings(CalendarSystem *system, CustomDateTime *globalTime, QObject *parent) :
    QObject(parent)
    , m_system(system)
    , m_globalTime(globalTime)
    , m_days(new QVector<DayOfWeek*>())
    , m_months(new QVector<Month*>())
{
    loadSettings();
}


Settings::~Settings()
{
    delete m_days;
    delete m_months;
    // writeSettings();
    if(m_db.isOpen())
        m_db.close();
}

void Settings::createDatabase(const QString& newConfig)
{
    m_db.addDatabase("QSQLITE");
    m_db.setDatabaseName(newConfig.append(".sqlite"));
    m_db.open();

    QSqlQuery queryDaysTable("CREATE TABLE IF NOT EXISTS days("
                            "id int not null primary key,"
                            "date text,"
                            "weekdayid int not null);");

    QSqlQuery queryEventsTable("CREATE TABLE IF NOT EXISTS events("
                               "id int not null primary key,"
                               "dayid int not null,"
                               "time text,"
                               "groupid int not null);");

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
    file.setFileName(QString("../%1").arg(m_currentConfig));

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
                        DayOfWeek *day = new DayOfWeek();
                        day->name = reader.readElementText();
                        reader.readNext();
                        day->id = reader.readElementText().toUInt();
                        m_days->append(day);
                        m_system->addDayOfWeek(day->name, day->id);
                    }
                    reader.readNext();
                }
            }
        }
}
    m_system->setTimeSystem(spm, mph, hpd);
    m_system->setDatabase(m_currentConfig);
    file.close();
    return true;
}


bool Settings::writeSettings()
{

    QFile file;
    QXmlStreamWriter writer(&file);
    file.setFileName(QString("../%1").arg(m_currentConfig));
    writer.writeStartDocument();
//-----------------------------------------------------
    writer.writeStartElement("settings");

    writer.writeStartElement("time system");

    writer.writeTextElement("seconds per minute", QString::number(m_system->m_secondsPerMinute()));
    writer.writeTextElement("minutes per hour", QString::number(m_system->m_minutesPerHour()));
    writer.writeTextElement("hours per day", QString::number(m_system->m_hoursPerDay()));

    writer.writeStartElement("days of week");
    for(DayOfWeek *day : *m_days)
    {
        writer.writeStartElement("day");
        writer.writeTextElement("day name", day->name);
        writer.writeTextElement("day id", QString::number(day->id));
        writer.writeEndElement();
    }
    writer.writeEndElement();

    writer.writeStartElement("months");
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
    writer.writeStartElement("event groups");

    for(EventGroup *group : m_groups)
    {
        writer.writeTextElement("group name", group->name);
        writer.writeAttribute("group id", QString::number(group->id));
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

void Settings::addDay_clicked()
{
    DayOfWeek *day = new DayOfWeek();
    day->id = QRandomGenerator::generate();
    day->name
}
