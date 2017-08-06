#ifndef _TEMPLATE_HPP_
#define _TEMPLATE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "Fragment.hpp"

class Template
{
    public:
        Template(unsigned int w, unsigned int h);
        Template(Fragment fragment);
        bool addFragment(Fragment fragment, int x, int y);
        bool scaleTemplate(unsigned int scale);
        SDL_Surface *getSurface();
        void close();
    private:
        SDL_Surface *templateSurface;
};

#endif
