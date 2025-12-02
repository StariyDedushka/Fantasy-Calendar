#include "include/logger.h"

Logger::Logger(const QString& filename)
{
    QString fullName = "../logs/";
    fullName.append(filename);
    fullName.append("-");
    fullName.append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
    logFile.setFileName(fullName);
    if(!logFile.open(QIODevice::WriteOnly))
        throw std::runtime_error("Could not open log file");
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
    bool crash = false;
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
        lvlStr = "WARNING";
        lvlStr = "WARN";
        break;
    case ERROR:
        lvlStr = "ERROR";
        break;
    case FATAL:
        lvlStr = "FATAL";
        crash = true;
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

    if(crash)
    {
        // throw std::exception() -- можно потом включить логирование фатальных ошибок
    }
}
