#ifndef _FRAGMENT_HPP_
#define _FRAGMENT_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class Fragment
{
    public:
        Fragment(std::string path);
        SDL_Surface *getSurface();
        void close();
    private:
        SDL_Surface *fragmentSurface;
};

#endif
