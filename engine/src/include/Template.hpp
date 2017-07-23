#ifndef _TEMPLATE_HPP_
#define _TEMPLATE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class Template
{
    public:
        Template(std::string path);
        SDL_Surface *getSurface();
        void close();
    private:
        SDL_Surface *templateSurface;
};

#endif
