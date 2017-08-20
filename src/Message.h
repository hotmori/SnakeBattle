#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>
class Message
{

public:
    Message(TTF_Font* pFont,
            SDL_Color color,
            const char* text);
    ~Message();
    TTF_Font* m_pFont;
    SDL_Color m_Color;
    const char* m_Text;
    SDL_Texture* m_pTexture;


private:

};
