#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QFileInfoList>
#include <QDateTime>
#include <QRegExp>


enum LogLevel { DEBUG, INFO, WARN, ERROR, FATAL};

class Logger {
public:
    Logger(LogLevel l, const QString& filename);
    ~Logger() { if(logFile.isOpen()) logFile.close(); }

    void operator()(LogLevel level,
                    QString const& message,
                    char const* function,
                    char const* logFile,
                    int line);
private:
    QFile logFile;
    LogLevel m_level;
};


#define LOG(Level_, Logger_, Message_)  \
Logger_(                 \
        Level_,          \
        Message_,        \
        __FUNCTION__,    \
        __FILE__,        \
        __LINE__         \
    )


#endif
