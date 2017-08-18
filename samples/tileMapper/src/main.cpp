#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lib/engine/engine.hpp"

SDL_Event event; //SDL_Event to handle user input
bool quit = false;
Window window(1024, 768);

std::vector<std::pair<unsigned char, int>> map = {
    std::pair<unsigned char, int>(0, 4),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(TILE_FLIP_Y, 4),
    std::pair<unsigned char, int>(0, 4),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(TILE_FLIP_Y, 4)
};

#define STATE_RED 0
#define STATE_BRICK 0

int main()
{
    if(!window.initialize())
    {
        return -1;
    }

    std::vector<SDL_Color> keys = std::vector<SDL_Color>();
    //Add the color key for our fragment
    SDL_Color colorKey;
    colorKey.r = 155;
    colorKey.g = 173;
    colorKey.b = 183;
    keys.push_back(colorKey);
    colorKey.r = 132;
    colorKey.g = 126;
    colorKey.b = 135;
    keys.push_back(colorKey);
    colorKey.r = 105;
    colorKey.g = 106;
    colorKey.b = 106;
    keys.push_back(colorKey);
    colorKey.r = 63;
    colorKey.g = 63;
    colorKey.b = 116;
    keys.push_back(colorKey);
    colorKey.r = 34;
    colorKey.g = 32;
    colorKey.b = 52;
    keys.push_back(colorKey);

    TileMap tileMap = TileMap();
    tileMap.renderStateMachine.addState(new RenderableState(STATE_RED, keys));
    tileMap.templateStateMachine.addState(new TemplateSheetState(STATE_BRICK, "resources/fragments/bricks.png", 16, 16, 2));

    tileMap.renderStateMachine.setCurrentState(STATE_RED);
    tileMap.templateStateMachine.setCurrentState(STATE_BRICK);
    tileMap.setMap(map, 4);

    // tileMap.templateStateMachine.currentState->setCurrentSprite(1);

    while(!quit)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            //If the user has quit the program close correctly
            if( event.type == SDL_QUIT )
            {
                quit = true;
                break;
            }else if(event.type == SDL_KEYDOWN){
                 switch(event.key.keysym.sym)
                 {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    default:
                        break;
                 }
            }
            window.clear();
            tileMap.render(window, -20, -20);
            //Update screen
            window.update();
        }
    }

    tileMap.freeAllStates();
    //Make sure to clear template cache
    TemplateState::freeAllTemplates();
    window.close();
}
