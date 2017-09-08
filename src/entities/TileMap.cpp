#include "../include/TileMap.hpp"

TileMap::TileMap(unsigned int width, unsigned int height, unsigned int tWidth, unsigned int tHeight)
{
    rowWidth = width;
    tileWidth = tWidth;
    tileHeight = tHeight;
    map = std::vector<Renderable*>(width * height, NULL);
}

bool TileMap::addTile(unsigned int x, unsigned int y, Renderable* tile)
{
    if(map.size() <= (rowWidth * y) + x)
    {
        return false;
    }
    map[(rowWidth * y) + x] = tile;
    return true;
}

Renderable* TileMap::getTile(unsigned int x, unsigned int y)
{
    if(map.size() <= (rowWidth * y) + x)
    {
        return NULL;
    }
    return map[(rowWidth * y) + x];
}

bool TileMap::render(Window window, int xPos, int yPos)
{
    int x = 0;
    int y = 0;

    //Loop through every tile in the map
    for(auto tile : map)
    {
        if(tile)
        {
            tile->setRenderPosition(xPos + (x * tileWidth), yPos + (y * tileHeight));
            tile->render(window);
        }
        //Move to next tile position
        x++;
        if(x >= rowWidth)
        {
            x = 0;
            y++;
        }
    }
}
