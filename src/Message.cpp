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
    m_pTexture = NULL;
}
Message::~Message() {
  if (m_pTexture != NULL)
    SDL_DestroyTexture(m_pTexture);
}
/*
SDL_Texture* Message::CreateTexture() {

  SDL_Surface* pSurfaceMessage;
  pSurfaceMessage = TTF_RenderText_Blended(this->m_pFont, this->m_Text,this->m_Color);


  SDL_Texture* pTextureMessage = SDL_CreateTextureFromSurface(m_Renderer, pSurfaceMessage);

  SDL_FreeSurface(pSurfaceMessage);
  return pTextureMessage;
}
*/
