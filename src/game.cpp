#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>

#include "game.hpp"
#include "graphics.hpp"
#include "input.hpp"
#include "player.hpp"
#include "util.hpp"

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

    std::cout<<"[CONTEXT] Running main loop"<<std::endl;

    try {

        this->_level = Level("maptest", graphics);
        this->_player = Player(graphics, this->_level.getPlayerSpawnPoint());

        int LAST_UPDATE_TIME = SDL_GetTicks();
        while(_gameRunning)
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
            {
                return;
            }
            else if(input.isKeyHeld(SDL_SCANCODE_LEFT))
            {
                this->_player.moveLeft();
            }
            else if(input.isKeyHeld(SDL_SCANCODE_RIGHT))
            {
                this->_player.moveRight();
            }
            
            if(!input.isKeyHeld(SDL_SCANCODE_RIGHT) and !input.isKeyHeld(SDL_SCANCODE_LEFT))
            {
                this->_player.stopMoving();
            }

            const int CURRENT_TIME = SDL_GetTicks();

            int timeElapsed = CURRENT_TIME - LAST_UPDATE_TIME;

            this->update(std::min(timeElapsed, MAX_FRAME_TIME));

            LAST_UPDATE_TIME = CURRENT_TIME;

            usleep(5);
        }

    } catch (const char * errorString) {

        Util::errorPrint((std::string) errorString + "\n    Aborting...");

    }
}

// ORDER MATTERS ON DRAWING

void Game::draw(Graphics & graphics)
{
    graphics.clear();
    
    this->_level.draw(graphics);
    this->_player.draw(graphics);
    
    graphics.flip();
}

void Game::update(float time)
{
    this->_level.update(time);
    this->_player.update(time);

    std::vector<Rectangle> others;
    if((others = this->_level.checkTileCollisions(this->_player.getBoundingBox())).size() > 0)
    {
        this->_player.handleTileCollisions(others);
        // _gameRunning = false;
    }
}

void Game::enableVerbose()
{
    Util::setVerbose(true);
}