// applicationcontext.h
#ifndef APPLICATIONCONTEXT_H
#define APPLICATIONCONTEXT_H

#include <QScopedPointer>
#include "calendarsystem.h"
#include "customdatetime.h"
#include "settings.h"

class ApplicationContext
{
private:
    QScopedPointer<CalendarSystem> m_calendarSystem;
    QScopedPointer<CustomDateTime> m_globalTime;
    QScopedPointer<Settings> m_settings;

public:
    ApplicationContext();

    CalendarSystem* calendarSystem() const { return m_calendarSystem.get(); }
    CustomDateTime* globalTime() const { return m_globalTime.get(); }
    Settings* settings() const { return m_settings.get(); }


    void initializeBasicSystems();
};

#endif // APPLICATIONCONTEXT_H
