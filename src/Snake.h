#pragma once

#include <SDL.h>
#include <deque>
#include <cstdlib>

#include "SnakeSegment.h"
#include "Coin.h"
#include "config.h"
#include "EventQueue.h"

static const unsigned COLLISION_NOT_HAPPENED = 0;
static const unsigned COLLISSION_HEAD_VS_BODY = 1;
static const unsigned COLLISION_HEAD_VS_HEAD = 2;


struct SKeyControls
{
    unsigned GoUpKey;
    unsigned GoDownKey;
    unsigned GoRightKey;
    unsigned GoLeftKey;
};

class Snake
{
public:
    Snake(SDL_Color headColor,
          SDL_Color segmentColor,
          Coin* pCoin,
          SKeyControls sKeys,
          unsigned ID);
    ~Snake();
    void Alive();
    void Update(Snake* pAnotherSnake);
    bool IsDead();
    unsigned GetSize();
    unsigned GetSegmentX(unsigned i);
    unsigned GetSegmentY(unsigned i);
    unsigned CheckForCollission(Snake* pSnake);
    void MoveThroughWall();
    void Kill();
    void CutTheTail();
    SDL_Color m_headColor;
    SDL_Color m_segmentColor;
private:
    std::deque<SnakeSegment> m_Segments;
    Coin* m_pCoin;
    unsigned m_Direction;
    bool CollissionAnSnakeBlocked;
    void UpdateDirection();
    void addSegment(unsigned x, unsigned y);
    void moveSnake();
    bool checkForWallCollission();
    bool checkForSelfCollission();
    bool checkForCoinCollission();
    unsigned m_ID;

    SKeyControls m_sKeys;
};
