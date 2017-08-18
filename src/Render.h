#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <string>

#include "Snake.h"
#include "config.h"
#include "Message.h"
#include "Logger.h"

class Render
{

public:
    Render();
    ~Render();
    void RenderBackground( );
    void RenderObject(Snake* pSnake);
    void RenderObject(Coin* pCoin);
    void RenderMessage(unsigned index, unsigned x = WINDOW_WIDTH/2, unsigned y = WINDOW_HEIGHT/2);
    void RenderMessage(Message &message, unsigned x = WINDOW_WIDTH/2, unsigned y = WINDOW_HEIGHT/2);
    SDL_Texture* CreateTextureForMessage(const char* TextMessage);
    SDL_Texture* CreateTexture(Message &message);
    void Display();
    void IniMessageTextures(Snake* pSnake1, Snake* pSnake2);
private:

    SDL_Renderer* m_Renderer;
    SDL_Window *m_pWindow;

    SDL_Rect m_RenderRect;

    TTF_Font* m_TextFont;
    SDL_Color m_TextColor;
    SDL_Texture* m_MessageTextures[MSG_MAX_COUNT];

};
