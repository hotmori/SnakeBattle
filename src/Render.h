#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Snake.h"
#include "config.h"

class Render
{

public:
    Render();
    ~Render();
    void RenderBackground( );
    void RenderObject(Snake* pSnake);
    void RenderObject(Coin* pCoin);
    void Display();
private:

    SDL_Renderer* m_Renderer;
    SDL_Window *m_pWindow;

    SDL_Rect m_RenderRect;
};
