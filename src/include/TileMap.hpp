#ifndef _TILEMAP_HPP_
#define _TILEMAP_HPP_

#include <vector>

#include "Renderable.hpp"
#include "TemplateSheetState.hpp"

#define TILE_NO_RENDER 1
#define TILE_FLIP_X 2
#define TILE_FLIP_Y 4

class TileMap : public Renderable
{
    public:
        StateMachine<TemplateSheetState> templateStateMachine;
        bool render(Window window, int xPos, int yPos);
        void setMap(std::vector<std::pair<unsigned char,int>> m, unsigned int r);
    private:
        unsigned int rowWidth;
        std::vector<std::pair<unsigned char,int>> map;
};

#endif
