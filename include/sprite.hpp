#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <string>

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

protected:
    SDL_Rect _sourceRect;
    SDL_Texture * _spriteSheet;

private:
    float _x, _y;
    
};

#endif