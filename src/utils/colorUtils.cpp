#include "colorUtils.hpp"

double luminance(SDL_Color color)
{
    //Digital weight
    return 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;
}

SDL_Color hslToRgb(HSL color)
{
    SDL_Color ret;
    double red;
    double green;
    double blue;
    double c = (1.0 - std::abs((2.0 * color.l) - 1.0)) * color.s;
    double huePrime = color.h / 60.0;
    double x = c * (1.0 - std::abs(fmod(huePrime, 2.0) - 1.0));
    double m = color.l - (c * 0.5);
    if(0 <= huePrime && huePrime < 1)
    {
        red = c;
        green = x;
        blue = 0;
    }else if(1 <= huePrime && huePrime < 2){
        red = x;
        green = c;
        blue = 0;
    }else if(2 <= huePrime && huePrime < 3){
        red = 0;
        green = c;
        blue = x;
    }else if(3 <= huePrime && huePrime < 4){
        red = 0;
        green = x;
        blue = c;
    }else if(4 <= huePrime && huePrime < 5){
        red = x;
        green = 0;
        blue = c;
    }else if(5 <= huePrime && huePrime < 6){
        red = c;
        green = 0;
        blue = x;
    }else{
        red = 0;
        green = 0;
        blue = 0;
    }

    red += m;
    green += m;
    blue += m;

    ret.r = (Uint8)round(red * 255);
    ret.g = (Uint8)round(green * 255);
    ret.b = (Uint8)round(blue * 255);

    return ret;
}

HSL rgbToHsl(SDL_Color color)
{
    HSL ret;
    double red = (int)color.r / 255.0;
    double green = (int)color.g / 255.0;
    double blue = (int)color.b / 255.0;
    double min;
    double max;
    double delta;
    double deltaR;
    double deltaG;
    double deltaB;

    min = std::min(std::min(red, green), blue);
    max = std::max(std::max(red, green), blue);
    delta = (max - min);
    ret.l = (max + min) / 2.0;

    if(delta == 0)
    {
        ret.h = 0;
        ret.s = 0;
    }else{
        if(ret.l < 0.5)
        {
            ret.s = delta / (max + min);
        }else{
            ret.s = delta / (2.0 - max - min);
        }

        deltaR = (((max - red) / 6.0) + (delta / 2.0)) / delta;
        deltaG = (((max - green) / 6.0) + (delta / 2.0)) / delta;
        deltaB = (((max - blue) / 6.0) + (delta / 2.0)) / delta;

        if(red == max)
        {
            ret.h = deltaB - deltaG;
        }else if(green == max){
            ret.h = (1.0 / 3.0) + deltaR - deltaB;
        }else if(blue == max){

            ret.h = (2.0 / 3.0) + deltaG - deltaR;
        }

        if(ret.h < 0.0)
        {
            ret.h += 1.0;
        }
        if(ret.h > 1.0)
        {
            ret.h -= 1.0;
        }
    }

    ret.h *= 360;
    return ret;
}

//TODO REMOVE COMMENT
/*************************************
*    |                               *
* 180 - - - - - - - - - - - -        *
*    |                               *
* 100 - - - - - - -X- <------- diff  *
*    |                               *
*    |          X                    *
*    |      X                        *
*  0 | X______________________       *
*      0   1    2   3  <------- i    *
*                                    *
*             y = mx^p               *
*************************************/
double getColor(double baseColor, unsigned int step, unsigned int i)
{
    // unsigned int diffA = abs((int)ambientColor - (int)baseColor);
    // unsigned int diffB = std::min(baseColor, ambientColor) + (360 - std::max(baseColor, ambientColor));
    // unsigned int diff = std::min(diffA, diffB);
    // //Value to adjust how step of a curve we want range 0 - 2
    // const double p = (1 - reflectiveness) * 2;
    //
    // //Solve for m
    // double m = diff / std::pow((double)numColors, p);
    // int newColor;
    //
    // if(diffA < diffB || baseColor > 360 / 2)
    // {
    //     newColor = round((double)baseColor + (m * std::pow((double)i, p)));
    // }else{
    //     newColor = round((double)baseColor - (m * std::pow((double)i, p)));
    // }

    double newColor;

    newColor = baseColor + (step * i);

    if(newColor > 360)
    {
        newColor -= 360;
    }

    if(newColor < 0)
    {
        newColor = 360 - abs(newColor);
    }

    return newColor;
}

/******************************************
*    |                                    *
*  1 - - - - - - - - - X - - - upperBound *
*    |                                    *
*    |              X                     *
*    |                                    *
*    |          X                         *
*    |      X                             *
*  0 | X______________________ lowerBound *
*      0    1   2   3   4  <----- i       *
*                                         *
*             y = mx^p + b                *
******************************************/
double getOffset(double p, double lowerBound, double upperBound, unsigned int i, unsigned int numColors)
{
    //Solve for m
    double m = (upperBound - lowerBound) / std::pow((double)numColors - 1, p);
    return m * std::pow((double)i, p) + lowerBound;
}

//Compare operator for SDL_Color so that std::map will work
bool operator<(const SDL_Color& a, const SDL_Color& b)
{
    return luminance(a) < luminance(b);
}

std::set<SDL_Color> getColorKeys(SDL_Surface* surface)
{
    std::set<SDL_Color> ret = std::set<SDL_Color>();
    SDL_Color pixelColor;
    for(int i = 0; i < surface->w * surface->h; i++)
    {
        pixelColor = getPixel(surface, i);
        if((int)pixelColor.a > 0)
        {
            ret.insert(pixelColor);
        }
    }
    return ret;
}
