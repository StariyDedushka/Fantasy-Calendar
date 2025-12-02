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
    std::unique_ptr<CalendarSystem> m_calendarSystem;
    std::unique_ptr<CustomDateTime> m_globalTime;
    std::unique_ptr<Settings> m_settings;

public:
    ApplicationContext();

    CalendarSystem* calendarSystem() const { return m_calendarSystem.get(); }
    CustomDateTime* globalTime() const { return m_globalTime.get(); }
    Settings* settings() const { return m_settings.get(); }


    void initializeBasicSystems();
};

#endif // APPLICATIONCONTEXT_H
