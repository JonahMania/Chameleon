#ifndef _TILEMAP_HPP_
#define _TILEMAP_HPP_

#include <vector>

#include "Renderable.hpp"

#define TILE_NO_RENDER 1
#define TILE_FLIP_X 2
#define TILE_FLIP_Y 4

class TileMap : public Renderable
{
    public:
        TileMap(unsigned int width, unsigned int height);
        bool addTile(unsigned int x, unsigned int y, int templateState, unsigned char o = 0);
        bool render(Window window, int xPos, int yPos);
    private:
        unsigned int rowWidth;
        std::vector<std::pair<unsigned char,int>> map;
};

#endif
