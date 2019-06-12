#include "graphics.hpp"
#include "globals.hpp"
#include "tile.hpp"

#include <SDL2/SDL.h>

Tile::Tile() {}

Tile::Tile(SDL_Texture * tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position) :
    _tileset(tileset),
    _size(size),
    _tilesetPosition(tilesetPosition),
    _position(position)
{}

void Tile::update(int elapsedTime) {}

void Tile::draw(Graphics & graphics)
{
    SDL_Rect dest = { (int) (this->_position.x * globals::SPRITE_SCALE), (int) (this->_position.y * globals::SPRITE_SCALE),
        (int) (this->_size.x * globals::SPRITE_SCALE), (int) (this->_size.y * globals::SPRITE_SCALE) };
    SDL_Rect source = { this->_tilesetPosition.x, this-> _tilesetPosition.y, this->_size.x, this->_size.y };
    graphics.blitSurface(this->_tileset, & source, & dest);
}