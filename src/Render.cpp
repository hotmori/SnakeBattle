#include "Render.h"

Render::Render(): m_Renderer ( NULL ), m_pWindow ( NULL )
{

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

    TTF_Font* Sans = TTF_OpenFont("FreeSans.ttf", 24); //this opens a font style and sets a size

    if (Sans == NULL) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Missing file",
                                 "File font is missing.",
                                 NULL);
    }
    SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color



    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

    //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

    //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    SDL_RenderCopy(m_Renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
/*    SDL_FreeSurface(surfaceMessage);
*/
    //Don't forget too free your surface and texture
    SDL_RenderPresent(m_Renderer);
    SDL_Delay(3000);

}
Render::~Render() {}

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
