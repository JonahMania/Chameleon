#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "../../../engine/engine.hpp"

#define NUM_STEPS  9
#define IMAGE_WIDTH  50
#define IMAGE_HEIGHT  50
#define SCALE 2
#define IMAGE_SPACING 2
#define BORDER_SIZE 10

SDL_Event event; //SDL_Event to handle user input
bool quit = false;
Timer frameTimer = Timer();
const int FPS = 30;
const int TIME_PER_FRAME = 1000 / FPS;

struct colorValues
{
    int hueBase = 0;
    int hueStep = 1;
    double reflectiveness = 0.0;
};

void updateScreen(colorValues cv, Colorable* image, Renderer* renderer)
{
    renderer->clear();

    image->setHue(cv.hueBase);
    image->setStep(cv.hueStep);
    image->setReflectiveness(cv.reflectiveness);

    for(int y = 0; y < NUM_STEPS; y++)
    {
        for(int x = 0; x < NUM_STEPS; x++)
        {
            image->setRenderPosition(BORDER_SIZE + (IMAGE_WIDTH * SCALE + IMAGE_SPACING) * x, BORDER_SIZE + (IMAGE_HEIGHT * SCALE + IMAGE_SPACING) * y);
            image->setSaturation(((double)1 / (double)NUM_STEPS) * (double)x);
            renderer->render(image);
        }
        image->setBrightness(((double)1 / (double)NUM_STEPS) * (double)y);
    }

    //Update screen
    renderer->update();
}

int main()
{
    int width = (IMAGE_WIDTH * SCALE + IMAGE_SPACING) * NUM_STEPS + BORDER_SIZE * 2;
    int height = (IMAGE_HEIGHT * SCALE + IMAGE_SPACING) * NUM_STEPS + BORDER_SIZE * 2;
    int currTime = 0;
    colorValues cv = colorValues();

    Renderer renderer = Renderer(width, height, 1);
    if(!renderer.initialize())
    {
        return -1;
    }
    //Don't cache textues since we will make a lot and only use them once
    renderer.disableRenderCache();

    Colorable image = Colorable("resources/trophy.png", IMAGE_WIDTH, IMAGE_HEIGHT, 0, 0, SCALE);

    cv.reflectiveness = image.getReflectiveness();

    updateScreen(cv, &image, &renderer);

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
                    //Quit
                    case SDLK_q:
                        quit = true;
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    //Change base Color
                    case SDLK_h:
                        cv.hueBase += 1;
                        if(cv.hueBase > 360)
                        {
                            cv.hueBase = 0;
                        }
                        break;
                    //Change step
                    case SDLK_s:
                        cv.hueStep += 1;
                        if(cv.hueStep > 60)
                        {
                            cv.hueStep = 0;
                        }
                        break;
                    //Change reflectiveness
                    case SDLK_r:
                        cv.reflectiveness += 0.01;
                        if(cv.reflectiveness > 1)
                        {
                            cv.reflectiveness = 0;
                        }
                }


                updateScreen(cv, &image, &renderer);

            }
        }

        //Cap frame rate
        currTime = frameTimer.getTime();
        if(currTime < TIME_PER_FRAME)
        {
            SDL_Delay(TIME_PER_FRAME - currTime);
        }
    }
}
