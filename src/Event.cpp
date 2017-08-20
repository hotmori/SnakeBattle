#include "Event.h"

Event::Event(unsigned evenType,
             unsigned counterNotification,
             unsigned playerID)
{
    this->m_EventType = evenType;
    this->m_CounterNotification = counterNotification;
    this->m_PlayerID = playerID;
}

void Event::DecrementCounter() {
   this->m_CounterNotification = this->m_CounterNotification - 1;
}
