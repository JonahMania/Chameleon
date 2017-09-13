#ifndef _TILEMAP_HPP_
#define _TILEMAP_HPP_

#include <vector>

#include "Renderable.hpp"

class TileMap
{
    public:
        TileMap();
        TileMap(unsigned int width, unsigned int height, unsigned int tWidth, unsigned int tHeight);
        bool addTile(unsigned int x, unsigned int y, Renderable* tile);
        Renderable* getTile(unsigned int x, unsigned int y);
        bool render(Window window, int xPos, int yPos);
    private:
        unsigned int rowWidth;
        unsigned int tileWidth;
        unsigned int tileHeight;
        std::vector<Renderable*> map;
};

#endif
