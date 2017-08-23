#include "Event.h"

Event::Event(unsigned evenType
            ,unsigned counterNotification
            ,Snake* snake
             )
{
    this->m_EventType = evenType;
    this->m_CounterNotification = counterNotification;
    this->m_Snake = snake;
}

void Event::DecrementCounter() {
   this->m_CounterNotification = this->m_CounterNotification - 1;
}
