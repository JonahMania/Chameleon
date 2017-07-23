#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath> //pow

#include "configParser.hpp"
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
int numColors = 5;

int main()
{
    std::cout<< "running main..." << std::endl;

    initialize();

    Palette *test = getPaletteFromConfig(std::string("resources/palettes/test.json"));
    Colorist *c = getColoristFromConfig("resources/coloristConfig.json");
    c->addPalette( "testPalette", test );
    Template t = Template("resources/templates/testTemplate.png");

    SDL_Surface *s = t.getSurface();

    if(s != NULL && test != NULL)
    {
        c->paintSurface("testPalette",s);
    }

    SDL_Rect bounds;
    SDL_Texture *testTexture = SDL_CreateTextureFromSurface( windowRenderer, s );
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = s->w;
    bounds.h = s->h;

    // SDL_Rect destR = new SDL_Rect

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

    delete test;
    delete c;
    t.close();
    close();
}
