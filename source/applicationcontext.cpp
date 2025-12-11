// applicationcontext.cpp
#include "include/applicationcontext.h"

ApplicationContext::ApplicationContext()
{
    m_calendarSystem = std::shared_ptr<CalendarSystem>(new CalendarSystem());
    m_globalTime = std::shared_ptr<CustomDateTime>(new CustomDateTime());
    m_settings = std::shared_ptr<Settings>(new Settings(m_calendarSystem.get(), m_globalTime.get()));
}

ApplicationContext::~ApplicationContext()
{
}

void ApplicationContext::initializeBasicSystems()
{
    // ... остальная инициализация
}
