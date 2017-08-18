#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lib/engine/engine.hpp"

SDL_Event event; //SDL_Event to handle user input
bool quit = false;
Window window(1024, 768);

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

    Renderable tile = Renderable();
    tile.renderStateMachine.addState(new RenderableState("redState", keys));
    tile.templateStateMachine.addState(new TemplateSheetState("simpleTile", "resources/fragments/bricks.png", 16, 16, 2));

    tile.renderStateMachine.setCurrentState("redState");
    tile.templateStateMachine.setCurrentState("simpleTile");
    ((TemplateSheetState*)tile.templateStateMachine.currentState)->setCurrentSprite(1);

    while( !quit )
    {
        while( SDL_PollEvent( &event ) != 0 )
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
            tile.render(window);
            //Update screen
            window.update();
        }
    }

    tile.freeAllStates();
    //Make sure to clear template cache
    TemplateState::freeAllTemplates();
    window.close();
}
