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
#include <iostream>
#include <unistd.h>
void Game::gameLoop()
{
    Graphics graphics;
    SDL_Event event;
    Input input;

    try {
        this->_player = AnimatedSprite(graphics, "./resources/char.png", 0, 0, 16, 16, 100 ,10, 100);
    } catch (const char * msg) {
        std::cout<<msg<<std::endl<<"ABORTING..."<<std::endl;
        return;
    }

    this->_player.setupAnimation();
    this->_player.playAnimation("runleft");

    int LAST_UPDATE_TIME = SDL_GetTicks();

    while(true)
    {
        draw(graphics);
        
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

        usleep(10000);
    }
}

void Game::draw(Graphics &graphics)
{
    graphics.clear();
    this->_player.draw(graphics, 100, 100);
    graphics.flip();
}

void Game::update(float time)
{
    this->_player.update(time);
}
