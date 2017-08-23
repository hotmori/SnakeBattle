#pragma once
#include <deque>
#include <cstdlib>

#include "Event.h"
#include "Logger.h"

class EventQueue {

  public:
    static std::deque<Event*> m_Events;

    static void AddEvent(Event* pEvent) {
      //LOG("%s Event: %d, PlayerID: %d", __FUNCTION__, pEvent->m_EventType, pEvent->m_PlayerID);
      EventQueue::m_Events.push_back(pEvent);
    }

    static Event* GetEvent(unsigned i) {
      Event* event = EventQueue::m_Events[i];
      if (event->m_CounterNotification > 0) {
        event->DecrementCounter();
      }
      else if (event->m_CounterNotification == 0) {
        EventQueue::m_Events.erase(EventQueue::m_Events.begin() + i);
        delete ( event );
        event = NULL;
      }
      return event;

    }

   ~EventQueue() {
       for (unsigned i = 0; i < EventQueue::m_Events.size(); i++) {
         delete ( (Event*)EventQueue::m_Events[i] );
       }

   }
};
