#include "Event.h"

Event::Event() {}

Event::Event(unsigned evenType
            ,unsigned counterNotification
             )
{
    this->m_EventType = evenType;
    this->m_CounterNotification = counterNotification;
}

void Event::DecrementCounter() {
   this->m_CounterNotification = this->m_CounterNotification - 1;
}

EventSnake::EventSnake(unsigned evenType
                      ,unsigned counterNotification
                      ,Snake* snake
                      )
{
    this->m_EventType = evenType;
    this->m_CounterNotification = counterNotification;
    this->m_Snake = snake;
}
