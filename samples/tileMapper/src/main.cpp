#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lib/engine/engine.hpp"

SDL_Event event; //SDL_Event to handle user input
bool quit = false;
Window window(1024, 768);
Timer frameTimer = Timer();
const int FPS = 30;
const int TIME_PER_FRAME = 1000 / FPS;

std::vector<std::pair<unsigned char, int>> map = {
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 5),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),

    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 5),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),

    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 5),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),

    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 5),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(TILE_FLIP_Y | TILE_FLIP_X, 1),
    std::pair<unsigned char, int>(0, 4),

    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 5),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(TILE_FLIP_Y | TILE_FLIP_X, 1),
    std::pair<unsigned char, int>(0, 4),

    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 5),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(TILE_FLIP_Y | TILE_FLIP_X, 1),
    std::pair<unsigned char, int>(0, 4),

    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 5),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(TILE_FLIP_Y | TILE_FLIP_X, 1),
    std::pair<unsigned char, int>(0, 4),
    std::pair<unsigned char, int>(0, 5),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(TILE_FLIP_Y | TILE_FLIP_X, 1),
    std::pair<unsigned char, int>(0, 4),

    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 5),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(TILE_FLIP_Y | TILE_FLIP_X, 1),
    std::pair<unsigned char, int>(0, 4),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 5),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(0, 15),
    std::pair<unsigned char, int>(TILE_FLIP_Y | TILE_FLIP_X, 1),
    std::pair<unsigned char, int>(0, 4),

    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0),
    std::pair<unsigned char, int>(0, 0)
};

#define STATE_RED_0 0
#define STATE_RED_1 1
#define STATE_RED_2 2
#define STATE_RED_3 3
#define STATE_RED_4 4
#define STATE_RED_5 5
#define STATE_RED_6 6
#define STATE_RED_7 7
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
    colorKey.r = 255;
    colorKey.g = 255;
    colorKey.b = 255;
    keys.push_back(colorKey);
    colorKey.r = 203;
    colorKey.g = 219;
    colorKey.b = 252;
    keys.push_back(colorKey);
    colorKey.r = 155;
    colorKey.g = 173;
    colorKey.b = 183;
    keys.push_back(colorKey);
    colorKey.r = 132;
    colorKey.g = 126;
    colorKey.b = 135;
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

    RenderableState* red_0 = new RenderableState(STATE_RED_0, keys);
    red_0->setReflectiveness(0.5);
    red_0->setSaturation(0.4);
    red_0->setBrightness(0.4);
    RenderableState* red_1 = new RenderableState(STATE_RED_1, keys);
    red_1->setReflectiveness(0.5);
    red_1->setSaturation(0.4);
    red_1->setBrightness(0.4);
    red_1->setAmbientColor(10);
    RenderableState* red_2 = new RenderableState(STATE_RED_2, keys);
    red_2->setReflectiveness(0.5);
    red_2->setSaturation(0.4);
    red_2->setBrightness(0.4);
    red_2->setAmbientColor(20);
    RenderableState* red_3 = new RenderableState(STATE_RED_3, keys);
    red_3->setReflectiveness(0.5);
    red_3->setSaturation(0.4);
    red_3->setBrightness(0.4);
    red_3->setAmbientColor(30);
    RenderableState* red_4 = new RenderableState(STATE_RED_4, keys);
    red_4->setReflectiveness(0.5);
    red_4->setSaturation(0.4);
    red_4->setBrightness(0.4);
    red_4->setAmbientColor(40);
    RenderableState* red_5 = new RenderableState(STATE_RED_5, keys);
    red_5->setReflectiveness(0.5);
    red_5->setSaturation(0.4);
    red_5->setBrightness(0.4);
    red_5->setAmbientColor(50);
    RenderableState* red_6 = new RenderableState(STATE_RED_6, keys);
    red_6->setReflectiveness(0.5);
    red_6->setSaturation(0.4);
    red_6->setBrightness(0.4);
    red_6->setAmbientColor(60);
    RenderableState* red_7 = new RenderableState(STATE_RED_7, keys);
    red_7->setReflectiveness(0.5);
    red_7->setSaturation(0.4);
    red_7->setBrightness(0.4);
    red_7->setAmbientColor(70);

    tileMap.renderStateMachine.addState(red_0);
    tileMap.renderStateMachine.addState(red_1);
    tileMap.renderStateMachine.addState(red_2);
    tileMap.renderStateMachine.addState(red_3);
    tileMap.renderStateMachine.addState(red_4);
    tileMap.templateStateMachine.addState(new TemplateSheetState(STATE_BRICK, "resources/fragments/bricks.png", 16, 16, 2));

    tileMap.renderStateMachine.setCurrentState(STATE_RED_0);
    tileMap.templateStateMachine.setCurrentState(STATE_BRICK);
    tileMap.setMap(map, 12);

    int currState = 0;
    int currTime = 0;
    while(!quit)
    {
        frameTimer.start();
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
                    case SDLK_q:
                        currState++;
                        if(currState > 7)
                        {
                            currState = 0;
                        }
                        tileMap.renderStateMachine.setCurrentState(currState);
                        break;
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
            currTime = frameTimer.getTime();
            if(currTime < TIME_PER_FRAME)
            {
                SDL_Delay(TIME_PER_FRAME - currTime);
            }
        }
    }

    tileMap.freeAllStates();
    //Make sure to clear template cache
    TemplateState::freeAllTemplates();
    window.close();
}
