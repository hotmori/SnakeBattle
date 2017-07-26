#include <iostream>
#include <deque>

#include <SDL.h>

#include "SnakeSegment.h"
#include "Coin.h"
#include "config.h"
#include "Snake.h"
#include "Render.h"

int main(int argc, char* argv[])
{
    unsigned time = 0;

    SDL_Event sdlEvent;

    SColor SnakeHeadColor, SnakeSegmentColor;
    SColor SnakeHeadColor2, SnakeSegmentColor2;


    bool isRunning;

    Render render;

    isRunning = true;

    CColor CoinColor;
    CoinColor.Red = 255;
    CoinColor.Green = 255;
    CoinColor.Blue = 0;
    CoinColor.Alpha = 255;
    Coin coin(CoinColor);

    SnakeHeadColor.Red = 255;
    SnakeHeadColor.Green = 0;
    SnakeHeadColor.Blue = 0;
    SnakeHeadColor.Alpha = 255;

    SnakeSegmentColor.Red = 0;
    SnakeSegmentColor.Green = 255;
    SnakeSegmentColor.Blue = 0;
    SnakeSegmentColor.Alpha = 255;

    SKeyControls sKeys;

    sKeys.GoUpKey = SDLK_UP;
    sKeys.GoDownKey = SDLK_DOWN;
    sKeys.GoRightKey = SDLK_RIGHT;
    sKeys.GoLeftKey = SDLK_LEFT;

    Snake snake(SnakeHeadColor, SnakeSegmentColor, &coin, sKeys, FIRST_PLAYER_ID);

    //Second snake

    SnakeHeadColor2.Red = 140;
    SnakeHeadColor2.Green = 0;
    SnakeHeadColor2.Blue = 140;
    SnakeHeadColor2.Alpha = 255;

    SnakeSegmentColor2.Red = 0;
    SnakeSegmentColor2.Green = 0;
    SnakeSegmentColor2.Blue = 200;
    SnakeSegmentColor2.Alpha = 255;

    SKeyControls sKeys2;

    sKeys2.GoUpKey = SDLK_w;
    sKeys2.GoDownKey = SDLK_s;
    sKeys2.GoRightKey = SDLK_d;
    sKeys2.GoLeftKey = SDLK_a;

    Snake snake2(SnakeHeadColor2, SnakeSegmentColor2, &coin, sKeys2, SECOND_PLAYER_ID);

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
        if (time >= RENDERING_TIMEOUT)
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

        if (snake.IsDead() && snake2.IsDead()) {
            render.RenderMessage(MSG_GAME_DRAW);
        }
        else if (snake.IsDead()) {
            render.RenderMessage(MSG_SECOND_PLAYER_WIN);
        }
        else if (snake2.IsDead()) {
            render.RenderMessage(MSG_FIRST_PLAYER_WIN);
        }
        render.Display();
    }
    SDL_Quit();

    return 0;
}
