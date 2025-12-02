// applicationcontext.cpp
#include "include/applicationcontext.h"

ApplicationContext::ApplicationContext()
{
    m_calendarSystem = std::make_unique<CalendarSystem>();
    m_globalTime = std::unique_ptr<CustomDateTime>();
    m_settings = std::unique_ptr<Settings>(m_calendarSystem, m_globalTime);
}

void ApplicationContext::initializeBasicSystems()
{
    // ... остальная инициализация
}
