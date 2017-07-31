#include "Render.h"

Render::Render(): m_Renderer ( NULL ), m_pWindow ( NULL )
{

   // This line is only needed, if you want debug the program
   //TODO
   SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL_Init Failed: "
                  << SDL_GetError() << std::endl;
    }

    m_pWindow = SDL_CreateWindow("Snake Battle",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             WINDOW_WIDTH, WINDOW_HEIGHT,
                             0
                             /*SDL_WINDOW_FULLSCREEN_DESKTOP*/);

    m_Renderer = SDL_CreateRenderer(m_pWindow, -1, 0);

    if (m_pWindow == NULL
        || m_Renderer == NULL
        || TTF_Init() == -1
        )
    {
        std::cerr << " Failed: "
                  << SDL_GetError() << std::endl;
    }

    this->IniMessages();

}
Render::~Render() {

    for (unsigned i=0; i < (MSG_MAX_COUNT-1); i++) {
        if (m_MessageTextures[i] != NULL) {
            SDL_DestroyTexture(m_MessageTextures[i]);
        }
    }

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_pWindow);
    TTF_Quit();
    SDL_Quit();
}

void Render::IniMessages() {

     m_TextFont = TTF_OpenFont(MSG_FONT, MSG_FONT_SIZE);

    if (m_TextFont == NULL) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Missing file",
                                 "File font is missing.",
                                 NULL);
    }
   m_TextColor.r = 255;
   m_TextColor.g = 255;
   m_TextColor.b = 255;
   m_TextColor.a = 0;

   for (unsigned i=0; i < (MSG_MAX_COUNT-1); i++) {
        m_MessageTextures[i] = NULL;
   }
   //typedef struct txt SDL_Texture;

   //std::map<Message, int> MessageTextureMap;
   std::map<Message, SDL_Texture*> MessageTextureMap;

   Message m1(m_TextFont, m_TextColor, (char*)"Cached message.");
   Message m2(m_TextFont, m_TextColor, (char*)"Cached message2.");

   //MessageTextureMap.insert(std::make_pair(m1, t));
   MessageTextureMap[m1] = this->CreateTexture(&m1);

   int texW = 0;
   int texH = 0;

   SDL_QueryTexture(MessageTextureMap[m1], NULL, NULL, &texW, &texH);
   SDL_Rect dstrect;

   dstrect.h = texH;
   dstrect.w = texW;
   //center align
   dstrect.x = 0;
   dstrect.y = 0;

   SDL_RenderCopy(m_Renderer, MessageTextureMap[m1], NULL, &dstrect);
   SDL_RenderPresent(m_Renderer);
   SDL_Delay(2001);

//   std::string s = std::to_string(1);
//   char const *pchar = s.c_str();  //use char const* as target type
   char buffer [33];
   itoa(MessageTextureMap.size(), buffer, 10);
   SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Debug 1",
                                 buffer,
                                 NULL);
   //2
   MessageTextureMap[m2] = this->CreateTexture(&m2);

   itoa(MessageTextureMap.size(), buffer, 10);
   SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Debug 2",
                                 buffer,
                                 NULL);
   texW = 0;
   texH = 0;

   SDL_QueryTexture(MessageTextureMap[m2], NULL, NULL, &texW, &texH);

   dstrect.h = texH;
   dstrect.w = texW;
   //center align
   dstrect.x = 0;
   dstrect.y = 0;

   SDL_RenderCopy(m_Renderer, MessageTextureMap[m2], NULL, &dstrect);
   SDL_RenderPresent(m_Renderer);
   SDL_Delay(2001);

   m_MessageTextures[MSG_GAME_START] = this->CreateTextureForMessage("Game started.");
   m_MessageTextures[MSG_GAME_OVER] = this->CreateTextureForMessage("Game over.");
   m_MessageTextures[MSG_FIRST_PLAYER_WIN] = this->CreateTextureForMessage("First player win!");
   m_MessageTextures[MSG_SECOND_PLAYER_WIN] = this->CreateTextureForMessage("Second player win!");
   m_MessageTextures[MSG_GAME_DRAW] = this->CreateTextureForMessage("Everybody won!");

}

SDL_Texture* Render::CreateTextureForMessage(const char* pTextMessage) {

  SDL_Surface* pSurfaceMessage = TTF_RenderText_Blended(m_TextFont, pTextMessage, m_TextColor);
  SDL_Texture* pTextureMessage = SDL_CreateTextureFromSurface(m_Renderer, pSurfaceMessage);

  SDL_FreeSurface(pSurfaceMessage);
  return pTextureMessage;
}

SDL_Texture* Render::CreateTexture(Message *pMessage) {

  SDL_Surface* pSurfaceMessage = TTF_RenderText_Blended(pMessage->m_pFont, pMessage->m_Text, pMessage->m_Color);
  SDL_Texture* pTextureMessage = SDL_CreateTextureFromSurface(m_Renderer, pSurfaceMessage);

  SDL_FreeSurface(pSurfaceMessage);
  return pTextureMessage;
}


void Render::RenderMessage(unsigned index, unsigned x, unsigned y) {

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(m_MessageTextures[index], NULL, NULL, &texW, &texH);
    SDL_Rect dstrect;
    dstrect.h = texH;
    dstrect.w = texW;
    //center align
    dstrect.x = x - texW/2;
    dstrect.y = y - texH/2;

    SDL_RenderCopy(m_Renderer, m_MessageTextures[index], NULL, &dstrect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
}

/*
void Render::RenderMessage(Message* pMessage, unsigned x, unsigned y) {

    int texW = 0;
    int texH = 0;

    SDL_QueryTexture(MessageTextureMap, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect;
    dstrect.h = texH;
    dstrect.w = texW;
    //center align
    dstrect.x = x - texW/2;
    dstrect.y = y - texH/2;

    SDL_RenderCopy(m_Renderer, m_MessageTextures[index], NULL, &dstrect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
}
*/

void Render::RenderBackground ()
{
   SDL_SetRenderDrawColor(m_Renderer, 0, 64, 0, 255);
   SDL_RenderFillRect(m_Renderer, NULL);
}

void Render::RenderObject(Snake* pSnake)
{
    if (pSnake->IsDead())
    {
        return;
    }
    //each coordinate (x and y) is multiplicated by cell size to get the right size of rendered rectangle
    //x and y are correspond to left upper corner of rectangle

    m_RenderRect.h = CELL_SIZE;
    m_RenderRect.w = CELL_SIZE;

    m_RenderRect.x = pSnake->GetSegmentX(0) * CELL_SIZE;
    m_RenderRect.y = pSnake->GetSegmentY(0) * CELL_SIZE;

    SDL_SetRenderDrawColor(m_Renderer, pSnake->m_headColor.Red,
                                       pSnake->m_headColor.Green,
                                       pSnake->m_headColor.Blue,
                                       pSnake->m_headColor.Alpha);

    SDL_RenderFillRect(m_Renderer, &m_RenderRect);

    for (unsigned i = 1; i < pSnake->GetSize(); i += 1)
    {
        m_RenderRect.x = pSnake->GetSegmentX(i) * CELL_SIZE;
        m_RenderRect.y = pSnake->GetSegmentY(i) * CELL_SIZE;

        SDL_SetRenderDrawColor(m_Renderer, pSnake->m_segmentColor.Red,
                                           pSnake->m_segmentColor.Green,
                                           pSnake->m_segmentColor.Blue,
                                           pSnake->m_segmentColor.Alpha);

        SDL_RenderFillRect(m_Renderer, &m_RenderRect);
    }
}

void Render::RenderObject(Coin* pCoin)
{

    if (!pCoin->IsAvailable())
    {
        return;
    }
    m_RenderRect.h = CELL_SIZE;
    m_RenderRect.w = CELL_SIZE;

    //each coordinate (x and y) is multiplicated by cell size to get the right size of rendered rectangle
    //x and y are correspond to left upper corner of rectangle
    m_RenderRect.x = pCoin->GetX() * CELL_SIZE;
    m_RenderRect.y = pCoin->GetY() * CELL_SIZE;

    SDL_SetRenderDrawColor(m_Renderer, pCoin->m_CoinColor.Red,
                                       pCoin->m_CoinColor.Green,
                                       pCoin->m_CoinColor.Blue,
                                       pCoin->m_CoinColor.Alpha);

    SDL_RenderFillRect(m_Renderer, &m_RenderRect);
}

void Render::Display()
{
    SDL_RenderPresent(m_Renderer);
    SDL_Delay(C_DELAY);
}
