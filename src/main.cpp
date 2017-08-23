#include <iostream>
#include <deque>
#include <stdio.h>
#include <SDL.h>
#include <unordered_map>

#include "SnakeSegment.h"
#include "Coin.h"
#include "config.h"
#include "Snake.h"
#include "Render.h"
#include "Logger.h"
#include "Event.h"
#include "EventQueue.h"

int main(int argc, char* argv[])
{

   Logger::ResetLog();

   LOG("Starting the game %s", __FUNCTION__);

    unsigned time = 0;

    SDL_Event sdlEvent;

    SDL_Color SnakeHeadColor, SnakeSegmentColor;
    SDL_Color SnakeHeadColor2, SnakeSegmentColor2;


    bool isRunning;

    Render render;

    isRunning = true;

    SDL_Color CoinColor;
    CoinColor.r = 255;
    CoinColor.g = 255;
    CoinColor.b = 0;
    CoinColor.a = 255;
    Coin coin(CoinColor);

    SnakeHeadColor.r = 255;
    SnakeHeadColor.g = 0;
    SnakeHeadColor.b = 0;
    SnakeHeadColor.a = 255;

    SnakeSegmentColor.r = 0;
    SnakeSegmentColor.g = 255;
    SnakeSegmentColor.b = 0;
    SnakeSegmentColor.a = 255;

    SKeyControls sKeys;

    sKeys.GoUpKey = SDLK_UP;
    sKeys.GoDownKey = SDLK_DOWN;
    sKeys.GoRightKey = SDLK_RIGHT;
    sKeys.GoLeftKey = SDLK_LEFT;

    Snake snake(SnakeHeadColor, SnakeSegmentColor, &coin, sKeys, FIRST_PLAYER_ID);

    //Second snake

    SnakeHeadColor2.r = 140;
    SnakeHeadColor2.g = 0;
    SnakeHeadColor2.b = 140;
    SnakeHeadColor2.a = 255;

    SnakeSegmentColor2.r = 0;
    SnakeSegmentColor2.g = 0;
    SnakeSegmentColor2.b = 255;
    SnakeSegmentColor2.a = 255;

    SKeyControls sKeys2;

    sKeys2.GoUpKey = SDLK_w;
    sKeys2.GoDownKey = SDLK_s;
    sKeys2.GoRightKey = SDLK_d;
    sKeys2.GoLeftKey = SDLK_a;

    Snake snake2(SnakeHeadColor2, SnakeSegmentColor2, &coin, sKeys2, SECOND_PLAYER_ID);

    render.IniMessageTextures(&snake, &snake2);

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

        for (unsigned i = 0; i < EventQueue::m_Events.size(); i++) {
          Event* pEvent = EventQueue::GetEvent(i);

          if (pEvent == NULL) {
            break;
          }

          render.RenderMessageForEvent(pEvent);
        }
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
