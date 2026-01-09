#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QFile>
#include <QtXml>
#include "calendarsystem.h"
#include "customdatetime.h"
#include "structs.h"


class Settings : public QObject
{
    Q_OBJECT

signals:
    void appliedChanges();
    void configRemoved(int i);
    void eventGroups_changed();

public slots:
    bool loadSettings();
    bool writeSettings();

    void dpm_valueChanged(int m_days, const QString& month);
    void secPerMin_valueChanged(int spm);
    void minPerHour_valueChanged(int mph);
    void hourPerDay_valueChanged(int hpd);
    void eventGroups_currentIndexChanged(const QString &group);
    void colorSelected(QColor color);
    void configs_currentIndexChanged(const QString& config);
    void loadConfig_clicked(const QString& config);
    void saveConfig_clicked(const QString& config);
    void btn_addConfig_clicked(const std::pair<int, QString>& config);
    void btn_removeConfig_clicked(const std::pair<int, QString>& config);

    void apply_clicked();
    void cancel_clicked();
    void addDay_clicked();

private:

    CalendarSystem* m_system;
    CustomDateTime* m_globalTime;
    QVector<EventContainerData> m_containers;
    QMap<quint16, QColor> containerColors;
    QVector<DayOfWeek> m_days;
    QVector<Month> m_months;
    QVector<std::pair<int, QString>> m_configs;
    std::pair<int, QString> m_currentConfig;
    QString m_configsPath;

    QSqlDatabase m_db;

    quint32 m_secondsPerMinute;
    quint32 m_minutesPerHour;
    quint32 m_hoursPerDay;

public:
    // Удаляем конструктор копирования и оператор присваивания
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
    Settings() = delete;

    Settings(CalendarSystem* system, CustomDateTime* globalTime, QObject *parent = nullptr);
    virtual ~Settings() override;
    void createDatabase(const QString& newConfig);
    EventContainerData getContainer(quint32 id) const;
};

#endif // SETTINGS_H
