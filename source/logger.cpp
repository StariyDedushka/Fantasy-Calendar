#include "include/logger.h"

Logger::Logger(LogLevel l, const QString& filename) : m_level(l)
{
    QString fullName = "../logs/";
    fullName.append(filename);
    fullName.append("-");
    fullName.append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
    logFile.setFileName(fullName);
    if(!logFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not open log file" << fullName;
    }
}

void Logger::operator()(LogLevel level,
                        QString const& message,
                        char const* function,
                        char const* file,
                        int line)
{
    QString lvlStr;
    switch(level)
    {
    case DEBUG:
        lvlStr = "DEBUG";
        break;
    case INFO:
        lvlStr = "INFO";
        break;
    case WARN:
        lvlStr = "WARN";
        break;
    case ERROR:
        lvlStr = "ERROR";
        break;
    }

    // Формируем строку лога
    QString logEntry = QString("%1 [%2] %3 in %4, line %5: %6\n")
                               .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))
                               .arg(lvlStr)
                               .arg(QString(file).section('/', -1)) // только имя файла без пути
                               .arg(function)
                               .arg(line)
                               .arg(message);

    // Записываем в файл
    QTextStream out(&logFile);
    out << logEntry;
    out.flush();

    // Также выводим в консоль
    qDebug() << logEntry.trimmed();
}
