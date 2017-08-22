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

#define STATE_RED_0 0
#define STATE_RED_1 1
#define STATE_RED_2 2
#define STATE_RED_3 3
#define STATE_RED_4 4
#define STATE_RED_5 5
#define STATE_RED_6 6
#define STATE_RED_7 7

#define BRICK_FILL 0
#define BRICK_EDGE_LEFT 1
#define BRICK_EDGE_RIGHT 2
#define BRICK_BACKGROUND 3

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

    TileMap tileMap = TileMap(13, 9);

    RenderableState* red_0 = new RenderableState(STATE_RED_0, keys);
    red_0->setReflectiveness(0.5);
    red_0->setSaturation(0.4);
    red_0->setBrightness(0.2);
    RenderableState* red_1 = new RenderableState(STATE_RED_1, keys);
    red_1->setReflectiveness(0.5);
    red_1->setSaturation(0.4);
    red_1->setBrightness(0.25);
    RenderableState* red_2 = new RenderableState(STATE_RED_2, keys);
    red_2->setReflectiveness(0.5);
    red_2->setSaturation(0.4);
    red_2->setBrightness(0.3);
    RenderableState* red_3 = new RenderableState(STATE_RED_3, keys);
    red_3->setReflectiveness(0.5);
    red_3->setSaturation(0.4);
    red_3->setBrightness(0.35);
    RenderableState* red_4 = new RenderableState(STATE_RED_4, keys);
    red_4->setReflectiveness(0.5);
    red_4->setSaturation(0.4);
    red_4->setBrightness(0.4);
    RenderableState* red_5 = new RenderableState(STATE_RED_5, keys);
    red_5->setReflectiveness(0.5);
    red_5->setSaturation(0.4);
    red_5->setBrightness(0.45);
    RenderableState* red_6 = new RenderableState(STATE_RED_6, keys);
    red_6->setReflectiveness(0.5);
    red_6->setSaturation(0.4);
    red_6->setBrightness(0.5);
    RenderableState* red_7 = new RenderableState(STATE_RED_7, keys);
    red_7->setReflectiveness(0.5);
    red_7->setSaturation(0.4);
    red_7->setBrightness(0.55);

    tileMap.renderStateMachine.addState(red_0);
    tileMap.renderStateMachine.addState(red_1);
    tileMap.renderStateMachine.addState(red_2);
    tileMap.renderStateMachine.addState(red_3);
    tileMap.renderStateMachine.addState(red_4);
    tileMap.templateStateMachine.addState(new TemplateState(BRICK_FILL, "resources/fragments/bricks.png", 16, 16, 0, 2));
    tileMap.templateStateMachine.addState(new TemplateState(BRICK_EDGE_LEFT, "resources/fragments/bricks.png", 16, 16, 4, 2));
    tileMap.templateStateMachine.addState(new TemplateState(BRICK_EDGE_RIGHT, "resources/fragments/bricks.png", 16, 16, 5, 2));
    tileMap.templateStateMachine.addState(new TemplateState(BRICK_BACKGROUND, "resources/fragments/bricks.png", 16, 16, 1, 2));

    tileMap.renderStateMachine.setCurrentState(STATE_RED_0);

    tileMap.addTile(0, 0, BRICK_FILL);
    tileMap.addTile(1, 0, BRICK_EDGE_RIGHT);
    tileMap.addTile(0, 1, BRICK_FILL);
    tileMap.addTile(1, 1, BRICK_EDGE_RIGHT);
    tileMap.addTile(0, 2, BRICK_FILL);
    tileMap.addTile(1, 2, BRICK_EDGE_RIGHT);
    tileMap.addTile(0, 3, BRICK_FILL);
    tileMap.addTile(1, 3, BRICK_EDGE_RIGHT);
    tileMap.addTile(11, 3, BRICK_BACKGROUND, TILE_FLIP_Y | TILE_FLIP_X);
    tileMap.addTile(12, 3, BRICK_EDGE_LEFT);
    tileMap.addTile(0, 4, BRICK_FILL);
    tileMap.addTile(1, 4, BRICK_EDGE_RIGHT);
    tileMap.addTile(11, 4, BRICK_BACKGROUND, TILE_FLIP_Y | TILE_FLIP_X);
    tileMap.addTile(12, 4, BRICK_EDGE_LEFT);
    tileMap.addTile(0, 5, BRICK_FILL);
    tileMap.addTile(1, 5, BRICK_EDGE_RIGHT);
    tileMap.addTile(11, 5, BRICK_BACKGROUND, TILE_FLIP_Y | TILE_FLIP_X);
    tileMap.addTile(12, 5, BRICK_EDGE_LEFT);
    tileMap.addTile(0, 6, BRICK_FILL);
    tileMap.addTile(1, 6, BRICK_EDGE_RIGHT);
    tileMap.addTile(3, 6, BRICK_BACKGROUND, TILE_FLIP_Y | TILE_FLIP_X);
    tileMap.addTile(4, 6, BRICK_EDGE_LEFT);
    tileMap.addTile(5, 6, BRICK_EDGE_RIGHT);
    tileMap.addTile(11, 6, BRICK_BACKGROUND, TILE_FLIP_Y | TILE_FLIP_X);
    tileMap.addTile(12, 6, BRICK_EDGE_LEFT);
    tileMap.addTile(0, 7, BRICK_FILL);
    tileMap.addTile(1, 7, BRICK_EDGE_RIGHT);
    tileMap.addTile(3, 7, BRICK_BACKGROUND, TILE_FLIP_Y | TILE_FLIP_X);
    tileMap.addTile(4, 7, BRICK_EDGE_LEFT);
    tileMap.addTile(5, 7, BRICK_FILL);
    tileMap.addTile(6, 7, BRICK_EDGE_RIGHT);
    tileMap.addTile(11, 7, BRICK_BACKGROUND, TILE_FLIP_Y | TILE_FLIP_X);
    tileMap.addTile(12, 7, BRICK_EDGE_LEFT);
    tileMap.addTile(0, 8, BRICK_FILL);
    tileMap.addTile(1, 8, BRICK_FILL);
    tileMap.addTile(2, 8, BRICK_FILL);
    tileMap.addTile(3, 8, BRICK_FILL);
    tileMap.addTile(4, 8, BRICK_FILL);
    tileMap.addTile(5, 8, BRICK_FILL);
    tileMap.addTile(6, 8, BRICK_FILL);
    tileMap.addTile(7, 8, BRICK_FILL);
    tileMap.addTile(8, 8, BRICK_FILL);
    tileMap.addTile(9, 8, BRICK_FILL);
    tileMap.addTile(10, 8, BRICK_FILL);
    tileMap.addTile(11, 8, BRICK_FILL);
    tileMap.addTile(12, 8, BRICK_FILL);


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
        }

        window.clear();
        tileMap.render(window,-20,-20);
        //Update screen
        window.update();
        //Cap frame rate
        currTime = frameTimer.getTime();
        if(currTime < TIME_PER_FRAME)
        {
            SDL_Delay(TIME_PER_FRAME - currTime);
        }

    }

    tileMap.freeAllStates();
    //Make sure to clear template cache
    TemplateState::freeAllTemplates();
    window.close();
}
