#include "Render.h"

Render::Render(): m_pDisplaySurface ( NULL )
{

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL_Init Failed: "
                  << SDL_GetError() << std::endl;
    }

    m_pDisplaySurface = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (m_pDisplaySurface == NULL)
    {
        std::cerr << "SDL_SetVideoMode Failed: "
                  << SDL_GetError() << std::endl;
    }

    m_BackGroundColor = this->GetMappedColor(0, 64, 0);

    SDL_WM_SetCaption("Snake Battle", NULL);
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
    SDL_Flip(m_pDisplaySurface);
    SDL_Delay(C_DELAY);
}

