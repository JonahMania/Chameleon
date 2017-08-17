#ifndef _COLORUTILS_HPP_
#define _COLORUTILS_HPP_

#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include <algorithm>

struct HSV
{
    HSV()
    {
        h = 0;
        s = 0;
        v = 0;
    }

    HSV(double hue, double saturation, double value)
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
        if(value > 1)
        {
            v = 1;
        }
        else if(value < 0)
        {
            v = 0;
        }
        else
        {
            v = value;
        }
    }
    double h;
    double s;
    double v;
};

double luminance(SDL_Color color);
SDL_Color hsvToRgb(HSV color);
HSV rgbToHsv(SDL_Color color);
unsigned int getColor(unsigned int baseColor, unsigned int ambientColor, double reflectiveness, unsigned int i, unsigned int numColors);
double getOffset(double p, double upperBound, unsigned int i, unsigned int numColors);

#endif
