#include "sprite.hpp"
#include "graphics.hpp"
#include "globals.hpp"
#include <iostream>

Sprite::Sprite() {}

Sprite::Sprite(Graphics & graphics, const std::string & path, int sourceX, int sourceY, int width, 
                int height, float posX, float posY) : 
                _x(posX),
                _y(posY)
{
    this->_sourceRect.x = sourceX;
    this->_sourceRect.y = sourceY;
    this->_sourceRect.w = width;
    this->_sourceRect.h = height;

    this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(path));
    if(_spriteSheet == NULL)
    {
        throw "Failed at creating surface texture from path '" + path + "'";
    }
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics & graphics, int x, int y)
{
    SDL_Rect  destination = { x, y, (int) (this->_sourceRect.w * globals::SPRITE_SCALE), (int) (this->_sourceRect.h * globals::SPRITE_SCALE) };
    graphics.blitSurface(this->_spriteSheet, & this->_sourceRect, & destination);
}

void Sprite::update()
{

}