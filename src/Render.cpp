#include "Render.h"

Render::Render(): m_pDisplaySurface ( NULL ), m_pWindow ( NULL )
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

    m_pDisplaySurface = SDL_GetWindowSurface( m_pWindow );

    if (m_pWindow == NULL
        || m_pDisplaySurface == NULL
        || TTF_Init() == -1
        )
    {
        std::cerr << " Failed: "
                  << SDL_GetError() << std::endl;
    }

    m_BackGroundColor = this->GetMappedColor(0, 64, 0);

}
Render::~Render() {}

void Render::RenderBackground ()
{
   SDL_FillRect(m_pDisplaySurface, NULL, m_BackGroundColor);
}

unsigned Render::GetMappedColor(unsigned Red, unsigned Green, unsigned Blue)
{
    return SDL_MapRGB(m_pDisplaySurface->format, Red, Green, Blue);
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

    SDL_FillRect(m_pDisplaySurface, &m_RenderRect, pSnake->GetHeadColor());

    for (unsigned i = 1; i < pSnake->GetSize(); i += 1)
    {
        m_RenderRect.x = pSnake->GetSegmentX(i) * CELL_SIZE;
        m_RenderRect.y = pSnake->GetSegmentY(i) * CELL_SIZE;

        SDL_FillRect(m_pDisplaySurface, &m_RenderRect, pSnake->GetSegmentColor());
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

    SDL_FillRect(m_pDisplaySurface, &m_RenderRect, pCoin->coinColor);
}

void Render::Display()
{
    SDL_UpdateWindowSurface( m_pWindow );
    SDL_Delay(C_DELAY);
}
