#pragma once
#include <cstddef>

static const unsigned EVENT_SNAKE_PLUS_SEGMENT = 1;
static const unsigned EVENT_SNAKE_MINUS_SEGMENT = 2;

static const unsigned NOTIFICATION_COUNTER = 150;
class Event {
  public:
    unsigned m_EventType;
    unsigned m_CounterNotification;
    unsigned m_PlayerID;
    Event(unsigned evenType,
          unsigned counterNotification = 1,
          unsigned playerID = (unsigned)NULL);
    void DecrementCounter();

};

