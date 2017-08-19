#include "Snake.h"

Snake::Snake(SDL_Color headColor,
             SDL_Color segmentColor,
             Coin* pCoin,
             SKeyControls sKeys,
             unsigned ID)
{
    this->m_headColor = headColor;
    this->m_segmentColor = segmentColor;
    this->m_pCoin = pCoin;
    this->m_sKeys = sKeys;
    this->m_ID = ID;

    this->Alive();
}

Snake::~Snake()
{
    this->m_Segments.clear();
}

void Snake::Alive()
{
    this->m_Segments.clear();

    unsigned start_x = 10 + rand() % (CELL_WIDTH - 12);
    unsigned start_y = 10 + rand() % (CELL_HEIGHT - 12);

    this->CollissionAnSnakeBlocked = false;

    //get random direction
    unsigned direction = rand() % 4;
    switch ( direction )
    {
    case 1:
        this->m_Direction = GO_RIGHT;
        for (unsigned i = 0; i < START_LENGTH; i += 1)
        {
            this->addSegment(start_x - i, start_y);
        }
        break;
    case 2:
        this->m_Direction = GO_LEFT;
        for (unsigned i = 0; i < START_LENGTH; i += 1)
        {
            this->addSegment(start_x + i, start_y);
        }
        break;
    case 3:
        this->m_Direction = GO_UP;
        for (unsigned i = 0; i < START_LENGTH; i += 1)
        {
            this->addSegment(start_x, start_y + i);
        }
        break;
    case 4:
        this->m_Direction = GO_DOWN;
        for (unsigned i = 0; i < START_LENGTH; i += 1)
        {
            this->addSegment(start_x, start_y - i);
        }
        break;
    }

}

void Snake::addSegment(unsigned x, unsigned y)
{
    SnakeSegment segment(x, y);
    this->m_Segments.push_back(segment);
}

bool Snake::checkForCoinCollission()
{
    unsigned headX = this->GetSegmentX(0);
    unsigned headY = this->GetSegmentY(0);
    unsigned coinX = m_pCoin->GetX();
    unsigned coinY = m_pCoin->GetY();

    return (headX == coinX) && (headY == coinY);
}
bool Snake::checkForSelfCollission()
{

    unsigned headX = this->GetSegmentX(0);
    unsigned headY = this->GetSegmentY(0);

    bool bresult = false;
    for (unsigned i = 1; i <= this->m_Segments.size() && !bresult; i++)
    {

        if (m_Segments[i].x == headX && m_Segments[i].y == headY)
        {
            bresult = true;
        }

    }
    return bresult;
}

//Move head in the one of four direction
void Snake::moveSnake()
{


    static const int moveX[] = { 0, 0, -1, 1 };
    static const int moveY[] = { -1, 1, 0, 0 };

    unsigned x = this->m_Segments[0].x + moveX[this->m_Direction];
    unsigned y = this->m_Segments[0].y + moveY[this->m_Direction];

    SnakeSegment segment(x, y);

    this->m_Segments.push_front(segment);
}

//refactor because of too many returns
void Snake::Update(Snake* pAnotherSnake)
{

    //check if snake is dead
    if (this->IsDead())
    {
        return;
    }

    //catch inputs
    this->UpdateDirection();
    this->MoveThroughWall();
    //if no action then check for collision and move
    if (this->checkForSelfCollission())
    {
        Event* pEvent = new Event(EVENT_SNAKE_MINUS_SEGMENT, 100, this->m_ID);
        EventQueue::AddEvent(pEvent);
        this->CutTheTail();
    }

    unsigned snakes_collided;
    snakes_collided = this->CheckForCollission(pAnotherSnake);

    switch ( snakes_collided )
    {
    //block on collission to avoid greedy behaviour
    //block is cleaned when first no collission move happened
    //however there is still issue with moving through walls
    case COLLISSION_HEAD_VS_BODY: {

        if (!this->CollissionAnSnakeBlocked)
        {
            this->CutTheTail();
            this->CollissionAnSnakeBlocked = true;
        }

          Event* pEvent = new Event(EVENT_SNAKE_MINUS_SEGMENT, 150, this->m_ID);
          EventQueue::AddEvent(pEvent);
        }
        break;
    case COLLISION_HEAD_VS_HEAD: {
            if (!this->CollissionAnSnakeBlocked)
            {
                this->CutTheTail();
                pAnotherSnake->CutTheTail();

                this->CollissionAnSnakeBlocked = true;
                pAnotherSnake->CollissionAnSnakeBlocked = true;

            }

            Event* pEvent = new Event(EVENT_SNAKE_MINUS_SEGMENT, 150, this->m_ID);
            EventQueue::AddEvent(pEvent);

        }
        break;
    case 0:
        this->CollissionAnSnakeBlocked = false;
        break;
    }

    if (IsDead())
    {
        return;
    }

    if (this->checkForCoinCollission())
    {

        Event* pEvent = new Event(EVENT_SNAKE_PLUS_SEGMENT, 100, this->m_ID);
        EventQueue::AddEvent(pEvent);
        //no cut of of the tail of a snake happens, that's why it gets longer
        //respawn coin, so it appears in new random place
        this->m_pCoin->Respawn();
    }
    else
    {
        // if no coin then cut off the tail of a snake
        this->CutTheTail();
    }
    //move in one possible direction
    this->moveSnake();
}

bool Snake::IsDead()
{
    return ( this->GetSize() == 0 );
}

void Snake::UpdateDirection()
{
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_GetScancodeFromKey(m_sKeys.GoUpKey)] && this->m_Direction != GO_DOWN)
    {
        this->m_Direction = GO_UP;
    }
    else if (keys[SDL_GetScancodeFromKey(m_sKeys.GoDownKey)] && this->m_Direction != GO_UP)
    {
        this->m_Direction = GO_DOWN;
    }
    else if (keys[SDL_GetScancodeFromKey(m_sKeys.GoRightKey)] && this->m_Direction != GO_LEFT)
    {
        this->m_Direction = GO_RIGHT;
    }
    else if (keys[SDL_GetScancodeFromKey(m_sKeys.GoLeftKey)] && this->m_Direction != GO_RIGHT)
    {
        this->m_Direction = GO_LEFT;
    }
}

unsigned Snake::GetSize()
{
    return this->m_Segments.size();
}
unsigned Snake::GetSegmentX(unsigned i)
{
    return this->m_Segments[i].x;
}
unsigned Snake::GetSegmentY(unsigned i)
{
    return this->m_Segments[i].y;
}

void Snake::Kill()
{
    this->m_Segments.clear();
}

unsigned Snake::CheckForCollission(Snake* pAnotherSnake)
{

    if (pAnotherSnake->IsDead())
    {
        return 0;
    }
    unsigned headX = this->m_Segments[0].x;
    unsigned headY = this->m_Segments[0].y;

    unsigned bresult = 0;
    for (unsigned i = 0; i <= pAnotherSnake->GetSize() && !bresult; i++)
    {

        if (pAnotherSnake->GetSegmentX(i) == headX && pAnotherSnake->GetSegmentY(i) == headY)
        {
            bresult = (i == 0) ? COLLISION_HEAD_VS_HEAD : COLLISSION_HEAD_VS_BODY;
        }

    }

    return bresult;
}

bool Snake::checkForWallCollission()
{

    unsigned headX = this->m_Segments[0].x;
    unsigned headY = this->m_Segments[0].y;

    return (headX == 0 || headY == 0 || headX == CELL_WIDTH || headY == CELL_HEIGHT);
}

void Snake::MoveThroughWall()
{
    for (unsigned i = 0; i <= this->GetSize(); i++)
    {

        if (this->m_Segments[i].x == 0)
        {
            this->m_Segments[i].x = CELL_WIDTH - 1;
        }
        else if (this->m_Segments[i].x == CELL_WIDTH)
        {
            this->m_Segments[i].x = 0 + 1;
        }
        else if (this->m_Segments[i].y == 0)
        {
            this->m_Segments[i].y = CELL_HEIGHT - 1;
        }
        else if (this->m_Segments[i].y == CELL_HEIGHT)
        {
            this->m_Segments[i].y = 0 + 1;
        }
    }
}

void Snake::CutTheTail()
{
    this->m_Segments.pop_back();
}
