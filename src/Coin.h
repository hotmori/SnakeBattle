#pragma once
#include <cstdlib>
#include <SDL.h>

class Coin
{
public:
    Coin(SDL_Color coinColor);
    void Respawn();
    unsigned GetX();
    unsigned GetY();
    SDL_Color m_CoinColor;
    bool IsAvailable();
    void Remove();
private:
    unsigned x;
    unsigned y;
    bool m_Available;

};
