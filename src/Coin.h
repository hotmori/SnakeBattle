#pragma once
#include <cstdlib>

struct CColor {
    unsigned Red;
    unsigned Green;
    unsigned Blue;
    unsigned Alpha;
};

class Coin
{
public:
    Coin(CColor coinColor);
    void Respawn();
    unsigned GetX();
    unsigned GetY();
    CColor m_CoinColor;
    bool IsAvailable();
    void Remove();
private:
    unsigned x;
    unsigned y;
    bool m_Available;

};
