#ifndef LEVEL_H
#define LEVEL_H

#include "globals.hpp"
#include "graphics.hpp"
#include "tile.hpp"
#include "rectangle.hpp"
#include "slopes.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <vector>

struct Tileset;

class Level
{
public:
    Level();
    Level(std::string mapName, Graphics & graphics);
    ~Level();
    void update(int elapsedTime);
    void draw(Graphics & graphics);

    std::vector<Rectangle> checkTileCollisions(const Rectangle & other);
    std::vector<Slope> checkSlopeCollisions(const Rectangle & other);

    const Vector2 getPlayerSpawnPoint() const;

private:
    std::string _mapName;
    Vector2 _spawnPoint;
    Vector2 _size;
    SDL_Texture * _backgroundTexture;

    Vector2 _tileSize;
    std::vector<Tile> _tileList;
    std::vector<Tileset> _tileSets;
    std::vector<Rectangle> _collisionRects;
    std::vector<Slope> _collisionSlopes;

    void loadMap(std::string mapName, Graphics & graphics);
};

struct Tileset
{
    SDL_Texture * _texture;
    int _firstGid;
    Tileset()
    {
        this->_firstGid = -1;
    }
    Tileset(SDL_Texture * texture, int firstGid) :
        _texture(texture),
        _firstGid(firstGid)
    {}
};

#endif