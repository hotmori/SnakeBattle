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
    void RenderMessage(unsigned index, unsigned x = 0, unsigned y = 0);
    void Display();
private:
    void IniMessages();
    SDL_Renderer* m_Renderer;
    SDL_Window *m_pWindow;

    SDL_Rect m_RenderRect;

    SDL_Texture* m_MessageTextures[50];
};
