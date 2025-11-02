// applicationcontext.cpp
#include "include/applicationcontext.h"

ApplicationContext::ApplicationContext()
{
    m_calendarSystem = std::make_unique<CalendarSystem>();
    m_globalTime = std::make_unique<CustomDateTime>(m_calendarSystem.get());
    m_settings = std::make_unique<Settings>(m_calendarSystem.get(), m_globalTime.get());
}

void ApplicationContext::initializeBasicSystems()
{
    m_calendarSystem->addDayOfWeek("Monday");
    m_calendarSystem->addDayOfWeek("Tuesday");
    m_calendarSystem->addDayOfWeek("Wednesday");
    // ... остальная инициализация
}
