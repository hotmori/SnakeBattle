#pragma once
#include <deque>
#include <cstdlib>

#include "Event.h"
#include "Logger.h"

class EventQueue {

  public:
    static std::deque<Event*> m_Events;

    static void AddEvent(Event* pEvent) {
      LOG("%s Event: %d, PlayerID: %d", __FUNCTION__, pEvent->m_EventType, pEvent->m_PlayerID);
      EventQueue::m_Events.push_back(pEvent);
    }

    static Event* GetEvent(unsigned i) {
      Event* event = EventQueue::m_Events[i];
      //LOG("%s %d", __FUNCTION__, event->m_EventType);
      if (event->m_CounterNotification > 0) {
        event->DecrementCounter();
      }
      else if (event->m_CounterNotification == 0) {
        //LOG("%s delete", __FUNCTION__);
        EventQueue::m_Events.erase(EventQueue::m_Events.begin() + i);
       // delete(event);
        //event = NULL;
      }
      return event;

    }


   ~EventQueue() {
       for (unsigned i = 0; i < EventQueue::m_Events.size(); i++) {
         //delete ( (Event*)EventQueue::m_Events[i] );
       }

   }
};


/*
Render::~Render() {

    for (unsigned i=0; i < (MSG_MAX_COUNT-1); i++) {
        if (m_MessageTextures[i] != NULL) {
            SDL_DestroyTexture(m_MessageTextures[i]);
        }
    }

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_pWindow);

    TTF_CloseFont(m_TextFont);
    TTF_Quit();
    SDL_Quit();
}

*/
//std::deque<Event*> m_Events;
