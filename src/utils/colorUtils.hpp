#ifndef _COLORUTILS_HPP_
#define _COLORUTILS_HPP_

#include <SDL.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <set>

#include "pixelAccess.hpp"

struct HSL
{
    HSL()
    {
        h = 0;
        s = 0;
        l = 0;
    }

    HSL(double hue, double saturation, double lightness)
    {
        if(hue > 360)
        {
            h = 360;
        }
        else if(hue < 0)
        {
            h = 0;
        }
        else
        {
            h = hue;
        }
        if(saturation > 1)
        {
            s = 1;
        }
        else if(saturation < 0)
        {
            s = 0;
        }
        else
        {
            s = saturation;
        }
        if(lightness > 1)
        {
            l = 1;
        }
        else if(lightness < 0)
        {
            l = 0;
        }
        else
        {
            l = lightness;
        }
    }
    double h;
    double s;
    double l;
};

double luminance(SDL_Color color);
SDL_Color hslToRgb(HSL color);
HSL rgbToHsl(SDL_Color color);
double getColor(double baseColor, unsigned int step, unsigned int i);
double getOffset(double p, double lowerBound, double upperBound, unsigned int i, unsigned int numColors);

//Compare operator for SDL_Color so that std::map will work
bool operator<(const SDL_Color& a, const SDL_Color& b);
//Custom compare used to sort colors
struct luminanceSort
{
    inline bool operator()(const SDL_Color& a, const SDL_Color& b)
    {
        return luminance(a) < luminance(b);
    }
};

std::set<SDL_Color> getColorKeys(SDL_Surface* surface);

#endif
