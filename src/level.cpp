#include "level.hpp"
#include "graphics.hpp"
#include "globals.hpp"
#include "tinyxml2.hpp"
#include "util.hpp"
#include "rectangle.hpp"

#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace tinyxml2;

Level::Level() {}

Level::Level(std::string mapName, Graphics & graphics) :
    _mapName(mapName),
    _size(Vector2(0,0))
{
    this->loadMap(mapName, graphics);
}

Level::~Level() {}

void Level::loadMap(std::string mapName, Graphics & graphics)
{
    XMLDocument doc;
    std::stringstream ss;
    ss << "resources/maps/" << mapName << ".tmx";

    if(!Util::fileExists(ss.str()))
    {
        throw "Map not found | Class: level";
    }

    doc.LoadFile(ss.str().c_str());

    XMLElement * mapNode = doc.FirstChildElement("map");

    int width, height;
    mapNode->QueryAttribute("width", &width);
    mapNode->QueryAttribute("height", &height);
    this->_size = Vector2(width, height);

    int tileWidth, tileHeight;
    mapNode->QueryAttribute("tilewidth", &tileWidth);
    mapNode->QueryAttribute("tileheight", &tileHeight);
    this->_tileSize = Vector2(tileWidth, tileHeight);

    Util::contextPrint("Map loaded: " + ss.str());
    Util::contextPrint("width: " + std::to_string(width) + " | height: " + std::to_string(height));
    Util::contextPrint("tileWidth: " + std::to_string(tileWidth) + " | tileHeight: " + std::to_string(tileHeight));

    XMLElement * pTileset = mapNode->FirstChildElement("tileset");
    if(pTileset != NULL)
    {
        while(pTileset)
        {
            int firstgid;
            const char * source = pTileset->Attribute("source");
            char * path;
            std::stringstream ss;
            ss << "resources/maps/" << source;

            std::string tilesetPath = ss.str();

            if(!Util::fileExists(tilesetPath))
            {
                throw "Tileset .png not found | Class: level";
            }

            if(tilesetPath.size() < 5 or tilesetPath.substr(tilesetPath.size() - 4) != ".png")
            {
                throw "Tileset has invalid file type, should be .png | Class: level";
            }

            pTileset->QueryIntAttribute("firstgid", &firstgid);
            SDL_Texture * tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(tilesetPath));
            this->_tileSets.push_back(Tileset(tex, firstgid));
            pTileset = pTileset->NextSiblingElement("tileset");
        }
    }
    
    XMLElement * player = mapNode->FirstChildElement("layer");
    if(player != NULL)
    {
        while(player)
        {
            XMLElement * pData = player->FirstChildElement("data");
            if(pData != NULL)
            {
                while(pData)
                {
                    XMLElement * pTile = pData->FirstChildElement("tile");
                    if(pTile != NULL)
                    {
                        int tileCounter = 0;
                        while(pTile)
                        {
                            int gid = pTile->IntAttribute("gid");
                            
                            if(gid == 0)
                            {
                                tileCounter++;
                                if(pTile = pTile->NextSiblingElement("tile"))
                                {
                                    continue;
                                }
                                else
                                {
                                    break;
                                }
                            }

                            Tileset tls;

                            for(Tileset & tileset : this->_tileSets)
                            {
                                if(tileset._firstGid <= gid)
                                {
                                    tls = tileset;
                                    break;
                                }
                            }

                            if(tls._firstGid == -1)
                            {
                                tileCounter++;
                                if(pTile->NextSiblingElement("tile"))
                                {
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                }
                                else
                                {
                                    break;
                                }
                            }

                            int xx, yy;

                            xx = tileCounter % width;
                            xx *= tileWidth;
                            yy = tileCounter / width;
                            yy *= tileHeight;

                            Vector2 finalTilePosition = Vector2(xx, yy);
                            
                            int tilesetWidth, tilesetHeight;
                            SDL_QueryTexture(tls._texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
                                               
                            int tsxx = gid % (tilesetWidth / tileWidth) - 1;
                            tsxx *= tileWidth;
                            int tsyy = 0;
                            int omt = (gid / (tilesetWidth / tileHeight));
                            tsyy = tileHeight * omt;

                            Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);
                            Tile tile(tls._texture, Vector2(tileWidth, tileHeight), 
                                finalTilesetPosition, finalTilePosition);

                            this->_tileList.push_back(tile);
                            tileCounter++;

                            pTile = pTile->NextSiblingElement("tile");
                        }
                    }
                    pData = pData->NextSiblingElement("data");
                }
            }
            player = player->NextSiblingElement("layer");
        }
    }

    bool cCollisionsPresent = false;
    bool cSpawnPointPresent = false;

    XMLElement * pObjectGroup = mapNode->FirstChildElement("objectgroup");
    if(pObjectGroup != NULL)
    {
        while(pObjectGroup)
        {
            const char * name = pObjectGroup->Attribute("name");
            std::stringstream objectGrouptype;
            objectGrouptype << name;

            if(objectGrouptype.str() == "collisions")
            {
                cCollisionsPresent = true;

                XMLElement * pObject = pObjectGroup->FirstChildElement("object");

                if(pObject != NULL)
                {
                    while(pObject)
                    {

                        int x, y, width, height;

                        x = pObject->FloatAttribute("x");
                        y = pObject->FloatAttribute("y");
                        width = pObject->FloatAttribute("width");
                        height = pObject->FloatAttribute("height");

                        Rectangle rect(
                            std::ceil(x) * globals::SPRITE_SCALE,
                            std::ceil(y) * globals::SPRITE_SCALE, 
                            std::ceil(width) * globals::SPRITE_SCALE, 
                            std::ceil(height) * globals::SPRITE_SCALE
                        );

                        this->_collisionRects.push_back(rect);

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
                else
                {
                    throw "Null object on collisions | Class: level";
                }
            } 
            
            if(objectGrouptype.str() == "spawn_points")
            {
                XMLElement * pObject = pObjectGroup->FirstChildElement("object");

                if(pObject != NULL)
                {
                    while(pObject)
                    {
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");
                        const char * name = pObject->Attribute("name");

                        std::stringstream ss;
                        ss << name;

                        if(ss.str() == "player")
                        {
                            cSpawnPointPresent = true;
                            this->_spawnPoint = Vector2(std::ceil(x) * globals::SPRITE_SCALE,
                                std::ceil(y) * globals::SPRITE_SCALE);
                        }

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }

            if(objectGrouptype.str() == "slopes")
            {
                XMLElement * pObject = pObjectGroup->FirstChildElement("object");

                if(pObject != NULL)
                {
                    while(pObject)
                    {
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");

                        std::vector<Vector2> points;
                        
                        Vector2 p1(
                            std::ceil(x),
                            std::ceil(y)
                        );

                        XMLElement * pPolyline = pObject->FirstChildElement("polyline");

                        if(pPolyline != NULL)
                        {
                            std::vector<std::string> pairs;
                            const char * pointString = pPolyline->Attribute("points");


                            std::stringstream ss;
                            ss << pointString;

                            for(std::string & pair : pairs)
                            {

                                std::vector<std::string> valsString;

                                Util::debugPrint(valsString[0] + ' ' + valsString[1]);

                                Util::split(pair, valsString, ',');



                                points.push_back(Vector2(
                                    std::stoi(valsString[0]),
                                    std::stoi(valsString[1])
                                ));
                            }

                            for(size_t i = 0; i < points.size(); i++)
                            {
                                this->_collisionSlopes.push_back(Slope(

                                        Vector2((int) (p1.x + points.at(i < 2 ? i : i - 1).x) * globals::SPRITE_SCALE,
                                            (int) (p1.y + points.at(i < 2 ? i : i - 1).y) * globals::SPRITE_SCALE),
                                        
                                        Vector2((int) (p1.x + points.at(i < 2 ? i + 1 : i).x) * globals::SPRITE_SCALE,
                                            (int) (p1.y + points.at(i < 2 ? i + 1 : i).y) * globals::SPRITE_SCALE)

                                ));
                            }



                        }

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }

            pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
        }
    }

    if(!cCollisionsPresent)
    {
        throw "No collisions present on map | Class: level";
    }

    if(!cSpawnPointPresent)
    {
        throw "No spawn points present on map | Class: level";
    }
    
}

void Level::update(int timeElapsed)
{

}

void Level::draw(Graphics & graphics)
{
    for(Tile & tile : _tileList)
    {
        tile.draw(graphics);
    }
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle & other)
{
    std::vector<Rectangle> collisions;
    for(Rectangle & rectangle : this->_collisionRects)
    {
        if(rectangle.collidesWith(other))
        {
            collisions.push_back(rectangle);
        }
    }
    return collisions;
}

const Vector2 Level::getPlayerSpawnPoint() const
{
    return this->_spawnPoint;
}