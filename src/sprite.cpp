#include "sprite.hpp"
#include "graphics.hpp"
#include "globals.hpp"
#include <iostream>
#include <algorithm>

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
        throw "Failed at creating surface texture from path | Class: Sprite";
    }

    this->_boundingBox = Rectangle(sourceX, sourceY, width * globals::SPRITE_SCALE, height * globals::SPRITE_SCALE);
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics & graphics, int x, int y)
{
    SDL_Rect  destination = { x, y, (int) (this->_sourceRect.w * globals::SPRITE_SCALE), (int) (this->_sourceRect.h * globals::SPRITE_SCALE) };
    graphics.blitSurface(this->_spriteSheet, & this->_sourceRect, & destination);
}

void Sprite::update()
{
    this->_boundingBox = Rectangle(this->_x, this->_y, 
        this->_sourceRect.w * globals::SPRITE_SCALE, this->_sourceRect.h * globals::SPRITE_SCALE);



}

const Rectangle Sprite::getBoundingBox() const
{
    return _boundingBox;
}

const sides::Side Sprite::getCollisionSide(Rectangle & other) const
{
    int amtRight, amtLeft, amtTop, amtBottom;
    amtRight = this->_boundingBox.getRight() - other.getLeft();
    amtLeft = this->_boundingBox.getLeft() - other.getRight();
    amtTop = this->_boundingBox.getTop() - other.getBottom();
    amtBottom = this->_boundingBox.getBottom() - other.getTop();

    std::pair<int, sides::Side> vals[4] = { {amtLeft, sides::LEFT}, 
    {amtRight, sides::RIGHT}, {amtBottom, sides::BOTTOM}, {amtTop, sides::TOP} };
    
    std::sort(vals, vals + 4);

    return  vals[0].second;
}