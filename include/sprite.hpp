#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <string>

#include "rectangle.hpp"
#include "globals.hpp"

class Graphics;

class Sprite 
{
public:
    Sprite();
    Sprite(Graphics & graphics, const std::string & path, int sourceX, int sourceY, int width, 
            int height, float posX, float posY);
    virtual ~Sprite();
    virtual void update();
    void draw(Graphics & graphics, int x, int y);

    Rectangle _boundingBox;

    const Rectangle getBoundingBox() const;
    const sides::Side getCollisionSide(Rectangle & other) const;

protected:
    SDL_Rect _sourceRect;
    SDL_Texture * _spriteSheet;
    float _x, _y;

private:
    
};

#endif