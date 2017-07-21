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
