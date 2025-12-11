// applicationcontext.h
#ifndef APPLICATIONCONTEXT_H
#define APPLICATIONCONTEXT_H

#include "calendarsystem.h"
#include "customdatetime.h"
#include "settings.h"
#include <memory>

class CalendarSystem;

class ApplicationContext
{
private:
    std::shared_ptr<CalendarSystem> m_calendarSystem;
    std::shared_ptr<CustomDateTime> m_globalTime;
    std::shared_ptr<Settings> m_settings;

public:
    ApplicationContext();
    ~ApplicationContext();

    CalendarSystem* calendarSystem() const { return m_calendarSystem.get(); }
    CustomDateTime* globalTime() const { return m_globalTime.get(); }
    Settings* settings() const { return m_settings.get(); }


    void initializeBasicSystems();
};

#endif // APPLICATIONCONTEXT_H
