#pragma once

class Snake;

static const unsigned EVENT_SNAKE_PLUS_SEGMENT = 1;
static const unsigned EVENT_SNAKE_MINUS_SEGMENT = 2;
static const unsigned EVENT_FIRST_PLAYER_WIN = 3;
static const unsigned EVENT_SECOND_PLAYER_WIN = 4;
static const unsigned EVENT_GAME_DRAW = 5;

static const unsigned NOTIFICATION_COUNTER = 150;
static const unsigned NOTIFICATION_COUNTER_GAME_OVER = 1500;

class Event {
  public:
    unsigned m_EventType;
    unsigned m_CounterNotification;
    void DecrementCounter();

    Snake* m_Snake;
    Event();
    Event(unsigned evenType
         ,unsigned counterNotification );
/*  TODO
    Event(unsigned evenType
          ,unsigned counterNotification);
    */

  virtual ~Event() {};
};

class EventSnake : public Event {
public:
    Snake* m_Snake;
    EventSnake(unsigned evenType
         ,unsigned counterNotification
         ,Snake* snake );
};
