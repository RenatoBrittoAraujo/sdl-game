#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "globals.hpp"

class Rectangle
{
public:
    Rectangle() {};

    Rectangle(int x, int y, int width, int height) :
        _x(x),
        _y(y),
        _width(width),
        _height(height)
    {}

    const int getCenterX() const { return this->_x + this->_width / 2; }
    const int getCenterY() const { return this->_y + this->_height / 2; }

    const int getLeft() const { return this->_x; }
    const int getRight() const { return this->_x + this->_width; }
    const int getTop() const { return this->_y; }
    const int getBottom() const { return this->_y + this->_height; }

    const int getHeight() const { return this->_height; }
    const int getWidth() const { return this->_width; }

    const int getSide(const sides::Side side) const 
    {
        return
            side == sides::LEFT     ? this->getLeft() :
            side == sides::RIGHT    ? this->getRight() :
            side == sides::TOP      ? this->getTop() : 
            side == sides::BOTTOM   ? this->getBottom() :
            sides::NONE;
    }

    const bool collidesWith(const Rectangle & other) const 
    {
        return
            this->getRight() >= other.getLeft() and
            this->getLeft() <= other.getRight() and
            this->getTop() <= other.getBottom() and
            this->getBottom() >= other.getTop();
    }

    const bool isValid() const 
    {
        return this->_x >= 0 and this->_y >= 0 and this->_width >= 0 and this->_height >= 0;
    }

    const inline Rectangle getRect() const { return *this; }

private:
    int _x, _y, _width, _height;
};

#endif