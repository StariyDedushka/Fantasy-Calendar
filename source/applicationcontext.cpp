// applicationcontext.cpp
#include "include/applicationcontext.h"

ApplicationContext::ApplicationContext()
{
    m_calendarSystem = new CalendarSystem();
    m_globalTime = new CustomDateTime();
    m_settings = new Settings(m_calendarSystem, m_globalTime);
}

ApplicationContext::~ApplicationContext()
{
    delete m_calendarSystem;
    delete m_globalTime;
    delete m_settings;
}

void ApplicationContext::initializeBasicSystems()
{
    // ... остальная инициализация
}
