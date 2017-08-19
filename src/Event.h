#pragma once
#include <cstddef>
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

