#include "../include/TileMap.hpp"

bool TileMap::render(Window window, int xPos, int yPos)
{
        int x = 0;
        int y = 0;
        SDL_Texture* temp;
        SDL_RendererFlip flip;

        //Loop through every tile in the map
        for(auto t : map)
        {
            //Set the current sprite to match the map data
            templateStateMachine.currentState->setCurrentSprite(t.second);
            //Create texture
            temp = renderStateMachine.currentState->getTexture(window.getRenderer(), templateStateMachine.currentState);
            dest.w = templateStateMachine.currentState->getBounds()->w;
            dest.h = templateStateMachine.currentState->getBounds()->h;
            //Calculate tile position in screen coordinates
            dest.x = (x * dest.w) - xPos;
            dest.y = (y * dest.w) - yPos;
            //Check if this tile is on the screen if not don't render it
            if((dest.x + dest.w) > 0 && dest.x < window.getWidth()
                && (dest.y + dest.h) > 0 && dest.y < window.getHeight())
            {
                flip = SDL_FLIP_NONE;
                if((t.first & TILE_FLIP_X) == TILE_FLIP_X)
                {
                    flip = SDL_FLIP_VERTICAL;
                }
                if((t.first & TILE_FLIP_Y) == TILE_FLIP_Y)
                {
                    flip = SDL_FLIP_HORIZONTAL;
                }
                if((t.first & (TILE_FLIP_X | TILE_FLIP_Y)) == (TILE_FLIP_X | TILE_FLIP_Y))
                {
                    flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
                }

                SDL_RenderCopyEx(window.getRenderer(), temp, templateStateMachine.currentState->getBounds(), &dest, 0, NULL, flip);
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

void TileMap::setMap(std::vector<std::pair<unsigned char, int>> m, unsigned int r)
{
    rowWidth = r;
    map = m;
}