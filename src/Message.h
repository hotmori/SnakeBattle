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
    //SDL_Texture* CreateTextureForMessage(SDL_Renderer* pRenderer);

    //operator is defined for map
    bool operator <(const Message& msg) const
    {
        //return id < rhs.id;
        int str_flg = strcmp(m_Text, msg.m_Text);
        return (str_flg == 0) ? false : true;
        /*
        return (strcmp(m_Text, msg.m_Text)
               && (m_Color.r == msg.m_Color.r
                   && m_Color.g == msg.m_Color.g
                   && m_Color.b == msg.m_Color.b
                   && m_Color.a == msg.m_Color.a))
                //TODO add font comparison
                  ;
       */
    }

private:

};
