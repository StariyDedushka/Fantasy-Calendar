// applicationcontext.cpp
#include "include/applicationcontext.h"

ApplicationContext::ApplicationContext()
{
    m_calendarSystem = QScopedPointer<CalendarSystem>();
    m_globalTime = QScopedPointer<CustomDateTime>(m_calendarSystem.get());
    m_settings = QScopedPointer<Settings>(m_calendarSystem.get(), m_globalTime.get());
}

void ApplicationContext::initializeBasicSystems()
{
    // ... остальная инициализация
}
