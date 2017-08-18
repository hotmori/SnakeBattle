#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>
class Message
{

public:
    Message(TTF_Font* pFont,
            SDL_Color color,
            char* text);
    ~Message();
    TTF_Font* m_pFont;
    SDL_Color m_Color;
    char* m_Text;
    SDL_Texture* m_pTexture;


private:

};
