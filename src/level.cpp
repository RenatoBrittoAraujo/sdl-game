#include "level.hpp"
#include "graphics.hpp"
#include "globals.hpp"
#include "tinyxml2.hpp"
#include "helpers.hpp"

#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace tinyxml2;

Level::Level() {}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics & graphics) :
    _mapName(mapName),
    _spawnPoint(spawnPoint),
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

    if(!fileExists(ss.str()))
    {
        throw "Map not found";
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

    contextPrint("Map loaded: " + ss.str());
    contextPrint("width: " + std::to_string(width) + " | height: " + std::to_string(height));
    contextPrint("tileWidth: " + std::to_string(tileWidth) + " | tileHeight: " + std::to_string(tileHeight));

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
            pTileset->QueryIntAttribute("firstgid", &firstgid);
            SDL_Texture * tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
            this->_tileSets.push_back(Tileset(tex, firstgid));
            pTileset = pTileset->NextSiblingElement("tileset");
        }
    }
    else
    {
        throw "Null tileset";
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

                            for(int i = 0; i < this->_tileSets.size(); i++)
                            {
                                if(this->_tileSets[i]._firstGid <= gid)
                                {
                                    tls = this->_tileSets.at(i);
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

                            int xx = 0;
                            int yy = 0;

                            xx = tileCounter % width;
                            xx *= tileWidth;
                            yy = tileCounter / width;
                            yy *= tileHeight;

                            Vector2 finalTilePosition = Vector2(xx, yy);
                            
                            int tilesetWidth, tilesetHeight;
                            SDL_QueryTexture(tls._texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
                            int tsxx = gid % (tilesetWidth / tilesetHeight) - 1;
                            tsxx *= tileWidth;
                            int tsyy = 0;
                            int omt = (gid / (tilesetWidth / tilesetHeight));
                            tsyy = tileHeight * omt;

                            Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);
                            Tile tile(tls._texture, Vector2(tileWidth, tileHeight), 
                                finalTilesetPosition, finalTilePosition);



                            this->_tileList.push_back(tile);
                            tileCounter++;

                            pTile = pTile->NextSiblingElement("tile");
                        }
                    }
                    else
                    {
                        throw "Empty tile";
                    }
                    
                    pData = pData->NextSiblingElement("data");
                }
            }
            else
            {
                throw "Empty data on layer";
            }
            
            player = player->NextSiblingElement("layer");
        }
    }
    else
    {
        throw "Empty layers on map";
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
