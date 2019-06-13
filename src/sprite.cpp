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
    this->_boundingBox = Rectangle(this->_x, this->_y, width * globals::SPRITE_SCALE, height * globals::SPRITE_SCALE);
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
    return this->_boundingBox;
}
#include "helpers.hpp"
const sides::Side Sprite::getCollisionSide(Rectangle & other) const
{
	int amtRight, amtLeft, amtTop, amtBottom;

	amtRight = this->getBoundingBox().getRight() - other.getLeft();
	amtLeft = other.getRight() - this->getBoundingBox().getLeft();
	amtTop = other.getBottom() - this->getBoundingBox().getTop();
	amtBottom = this->getBoundingBox().getBottom() - other.getTop();

	int vals[4] = { abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom) };
	int lowest = vals[0];
	for (int i = 0; i < 4; i++) {
		if (vals[i] < lowest) {
			lowest = vals[i];
		}
	}

	return
			lowest == abs(amtRight) ? sides::RIGHT :
			lowest == abs(amtLeft) ? sides::LEFT :
			lowest == abs(amtTop) ? sides::TOP :
			lowest == abs(amtBottom) ? sides::BOTTOM :
			sides::NONE;

}
