#include "Coin.h"
#include "config.h"

Coin::Coin(SDL_Color coinColor)
{
    this->m_CoinColor = coinColor;
    this->Respawn();
}

void Coin::Respawn()
{
    this->x = 1 + rand() % (CELL_WIDTH - 2);
    this->y = 1 + rand() % (CELL_HEIGHT - 2);
    this->m_Available = true;
}

unsigned Coin::GetX()
{
    return this->x;
}
unsigned Coin::GetY()
{
    return this->y;
}

bool Coin::IsAvailable()
{
    return this->m_Available;
}

void Coin::Remove()
{
    m_Available = false;
}
