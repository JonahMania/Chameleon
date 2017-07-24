#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lib/engine/engine.hpp"

const int screenWidth = 1024; //Width of the game window
const int screenHeight = 768; //Height of the game window

SDL_Window* window = NULL;
SDL_Renderer* windowRenderer = NULL;
SDL_Rect windowRect = { 0, 0, screenWidth, screenHeight };
SDL_Event event; //SDL_Event to handle user input

bool quit = false;

//Initialize the window and screen
bool initialize()
{
    //Initialize SDL library
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cerr << "ERROR: SDL could not initialize " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "colorGen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            std::cerr << "ERROR: Window was not created " << SDL_GetError() << std::endl;
            return false;
        }
        else
        {
            //Create rendering context for window
            windowRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC );
            if( windowRenderer == NULL )
            {
                std::cerr << "ERROR: renderer cound not be created " << SDL_GetError() << std::endl;
                return false;
            }
            else
            {
                //Initilize PNG loading
                if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
                {
                    std::cerr << "ERROR: PNG loading was not initilized " << IMG_GetError() << std::endl;
                    return false;
                }
            }
        }
    }
    return true;
}

void close()
{
    SDL_DestroyRenderer( windowRenderer );
    SDL_DestroyWindow( window );
    windowRenderer = NULL;
    window = NULL;
    SDL_Quit();
}

int main()
{
    if( !initialize() )
    {
        return -1;
    }

    Palette testPalette = Palette();
    Colorist testColorist = Colorist();
    Fragment testFragment = Fragment("resources/fragments/testFragment.png");
    Template testTemplate = Template(16, 16);

    //Add the color key for our fragment
    SDL_Color colorKey;
    colorKey.r = 155;
    colorKey.g = 173;
    colorKey.b = 183;
    testColorist.pushColorKey(colorKey);
    colorKey.r = 132;
    colorKey.g = 126;
    colorKey.b = 135;
    testColorist.pushColorKey(colorKey);
    colorKey.r = 105;
    colorKey.g = 106;
    colorKey.b = 106;
    testColorist.pushColorKey(colorKey);
    colorKey.r = 63;
    colorKey.g = 63;
    colorKey.b = 116;
    testColorist.pushColorKey(colorKey);
    colorKey.r = 34;
    colorKey.g = 32;
    colorKey.b = 52;
    testColorist.pushColorKey(colorKey);

    testColorist.addPalette("testPalette", &testPalette);
    testTemplate.addFragment(testFragment, 0, 0);

    testTemplate.scaleTemplate(3);
    SDL_Surface *testSurface = testTemplate.getSurface();
    testColorist.paintSurface("testPalette", testSurface);

    SDL_Rect bounds;
    SDL_Texture *testTexture = SDL_CreateTextureFromSurface( windowRenderer, testSurface );
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = testSurface->w;
    bounds.h = testSurface->h;

    while( !quit )
    {
        while( SDL_PollEvent( &event ) != 0 )
        {
            //If the user has quit the program close correctly
            if( event.type == SDL_QUIT )
            {
            quit = true;
            break;
            }

            //Render Background as black
            SDL_SetRenderDrawColor( windowRenderer, 0, 0, 0, 0xFF );
            SDL_RenderClear( windowRenderer );
            SDL_RenderCopy( windowRenderer, testTexture, &bounds, &bounds );
            //Update screen
            SDL_RenderPresent( windowRenderer );
        }
    }

    testFragment.close();
    testTemplate.close();
    close();
}
