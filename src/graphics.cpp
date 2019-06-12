#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "graphics.hpp"
#include "helpers.hpp"
#include "globals.hpp"

#define GAME_NAME "Prototyper"

Graphics::Graphics()
{
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, GAME_NAME);
}

Graphics::~Graphics()
{
    SDL_DestroyWindow(this->_window);
    SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface * Graphics::loadImage(const std::string & path)
{
    if(!fileExists(path))
    {
        throw "Failed at finding image file | Class: Graphics";
    }   
    if(!this->_spriteSheets.count(path))
    {
        this->_spriteSheets[path] = IMG_Load(path.c_str());
    }
    return this->_spriteSheets[path];
}

void Graphics::blitSurface(SDL_Texture * texture, SDL_Rect * source, SDL_Rect * destination)
{
    SDL_RenderCopy(this->_renderer, texture, source, destination);
}

void Graphics::flip()
{
    SDL_RenderPresent(this->_renderer);
}

void Graphics::clear()
{
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer * Graphics::getRenderer() const {
    return this->_renderer;
}