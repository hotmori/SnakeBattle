#include <string.h>
#include "Message.h"

Message::Message(
                 TTF_Font* pFont,
                 SDL_Color color,
                 const char* text
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
