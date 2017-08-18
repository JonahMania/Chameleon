#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Window
{
    public:
        Window(int w, int h);
        bool initialize();
        int getHeight();
        int getWidth();
        //Clear the screen to black
        bool clear();
        //Update the latest changes to the screen
        void update();
        void render(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dest);
        SDL_Renderer* getRenderer();
        void close();
    private:
        int width;
        int height;
        SDL_Window* window;
        SDL_Renderer* windowRenderer;
        SDL_Rect windowRect;
};

#endif
