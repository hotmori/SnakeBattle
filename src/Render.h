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
    void RenderMessage(unsigned index, unsigned x = WINDOW_WIDTH/2, unsigned y = WINDOW_HEIGHT/2);
    SDL_Texture* CreateTextureForMessage(const char* TextMessage);
    void Display();
private:
    void IniMessages();
    SDL_Renderer* m_Renderer;
    SDL_Window *m_pWindow;

    SDL_Rect m_RenderRect;

    TTF_Font* m_TextFont;
    SDL_Color m_TextColor;
    SDL_Texture* m_MessageTextures[MSG_MAX_COUNT];
};
