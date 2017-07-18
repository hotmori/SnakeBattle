#include <iostream>
#include <deque>
#include <SDL/SDL.h>

#include "SnakeSegment.h"
#include "Coin.h"
#include "config.h"
#include "Snake.h"
#include "Render.h"

int main(int argc, char* argv[])
{

    unsigned time = 0;
    unsigned timeout = 6;

    SDL_Event sdlEvent;

    unsigned SnakeHeadColor, SnakeHeadColor2;
    unsigned SnakeSegmentColor, SnakeSegmentColor2;

    unsigned CoinColor;
    bool isRunning;

    Render render;

    CoinColor = render.GetMappedColor( 255, 255, 0);
    Coin coin(CoinColor);

    isRunning = true;

    SnakeHeadColor = render.GetMappedColor( 255, 0, 0);
    SnakeSegmentColor = render.GetMappedColor( 0, 255, 0);

    SKeyControls sKeys;

    sKeys.GoUpKey = SDLK_UP;
    sKeys.GoDownKey = SDLK_DOWN;
    sKeys.GoRightKey = SDLK_RIGHT;
    sKeys.GoLeftKey = SDLK_LEFT;

    Snake snake(SnakeHeadColor, SnakeSegmentColor, &coin, sKeys, 1);

    //Second snake
    SnakeHeadColor2 = render.GetMappedColor( 140, 0, 140);
    SnakeSegmentColor2 = render.GetMappedColor( 0, 0, 200);

    SKeyControls sKeys2;

    sKeys2.GoUpKey = SDLK_w;
    sKeys2.GoDownKey = SDLK_s;
    sKeys2.GoRightKey = SDLK_d;
    sKeys2.GoLeftKey = SDLK_a;

    Snake snake2(SnakeHeadColor2, SnakeSegmentColor2, &coin, sKeys2, 2);

    while(isRunning)
    {
        //handle events
        while(SDL_PollEvent(&sdlEvent))
        {
            switch(sdlEvent.type)
            {
            case SDL_QUIT:
            {
                isRunning = false;
            }
            break;
            case SDL_KEYDOWN:
            {
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
                else if (sdlEvent.key.keysym.sym == SDLK_RETURN)
                {
                    if(snake.IsDead() || snake2.IsDead() )
                    {
                        snake.Alive();
                        snake2.Alive();
                        coin.Respawn();
                    }
                }
            }
            break;
            }
        }
        //Movements

        //some delay for player(s)
        time += 1;
        if (time >= timeout)
        {
            snake.Update(&snake2);
            snake2.Update(&snake);
            time = 0;
        }

        //render game background
        render.RenderBackground();

        render.RenderObject(&snake);
        render.RenderObject(&snake2);
        render.RenderObject(&coin);

        render.Display();
    }

    SDL_Quit();

    return 0;
}
