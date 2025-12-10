// applicationcontext.h
#ifndef APPLICATIONCONTEXT_H
#define APPLICATIONCONTEXT_H

#include "calendarsystem.h"
#include "customdatetime.h"
#include "settings.h"

class ApplicationContext
{
private:
    CalendarSystem *m_calendarSystem;
    CustomDateTime *m_globalTime;
    Settings *m_settings;

public:
    ApplicationContext();
    ~ApplicationContext();

    CalendarSystem* calendarSystem() const { return m_calendarSystem; }
    CustomDateTime* globalTime() const { return m_globalTime; }
    Settings* settings() const { return m_settings; }


    void initializeBasicSystems();
};

#endif // APPLICATIONCONTEXT_H
