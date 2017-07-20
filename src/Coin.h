#pragma once
#include <cstdlib>

class Coin
{
public:

    Coin(unsigned coinColor);
    void Respawn();
    unsigned GetX();
    unsigned GetY();
    unsigned coinColor;
    bool IsAvailable();
    void Remove();
private:
    unsigned x;
    unsigned y;
    bool m_Available;

};
