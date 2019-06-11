#include <SDL2/SDL.h>

#include "game.hpp"
#include "graphics.hpp"
#include "input.hpp"

namespace {
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

Game::~Game()
{

}

void Game::gameLoop()
{
    Graphics graphics;
    SDL_Event event;
    Input input;

    int LAST_UPDATE_TIME = SDL_GetTicks();

    while(true)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                return;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                if(event.key.repeat == 0)
                    input.keyDownEvent(event);
            }
            else if(event.type == SDL_KEYUP)
            {
                input.keyUpEvent(event);
            }
        }
        if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
            return;

        const int CURRENT_TIME = SDL_GetTicks();

        int timeElapsed = CURRENT_TIME - LAST_UPDATE_TIME;

        this->update(std::min(timeElapsed, MAX_FRAME_TIME));

        LAST_UPDATE_TIME = CURRENT_TIME;
    }
}

void Game::draw(Graphics &graphics)
{

}

void Game::update(float time)
{

}
