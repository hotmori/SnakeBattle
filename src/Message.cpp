#include <string.h>
#include "Message.h"

Message::Message(
                 TTF_Font* pFont,
                 SDL_Color color,
                 char* text
                 )
{
    m_pFont = pFont;
    m_Color = color;
    m_Text = text;
}
Message::~Message() {

}

/*
SDL_Texture* Message::CreateTextureForMessage(SDL_Renderer* pRenderer) {
  SDL_Surface* pSurfaceMessage = TTF_RenderText_Blended(m_pFont, m_Text, m_Color);
  SDL_Texture* pTextureMessage = SDL_CreateTextureFromSurface(pRenderer, pSurfaceMessage);

  SDL_FreeSurface(pSurfaceMessage);
  return pTextureMessage;
}
*/
