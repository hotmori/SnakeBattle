#include <SDL2/SDL.h>
#include <iostream>
#include "Snake.h"
#include "config.h"

class Render
{

public:
    Render();
    ~Render();
    unsigned GetMappedColor(unsigned Red, unsigned Green, unsigned Blue);
    void RenderBackground( );
    void RenderObject(Snake* pSnake);
    void RenderObject(Coin* pCoin);
    void Display();
private:
    unsigned m_BackGroundColor;
    SDL_Surface* m_pDisplaySurface;
    SDL_Window *m_pWindow;

    SDL_Rect m_RenderRect;
};
