#include "include/calendarsystem.h"

CalendarSystem* CalendarSystem::instance_ptr = nullptr;

CalendarSystem* CalendarSystem::getInstance()
{
    if(instance_ptr == nullptr)
        instance_ptr = new CalendarSystem();
    return instance_ptr;
}

