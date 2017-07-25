#ifndef _COLOR_NORMAL_HPP_
#define _COLOR_NORMAL_HPP_

#include <SDL2/SDL.h>

struct ColorNormal
{
    double r;
    double g;
    double b;

    ColorNormal();
    ColorNormal(SDL_Color color);
    SDL_Color toSDL_Color();
    ColorNormal operator*(ColorNormal color);
    ColorNormal operator*(double scale);
    ColorNormal operator+(ColorNormal color);
};


#endif
