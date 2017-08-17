#include "colorUtils.hpp"

double luminance(SDL_Color color)
{
    //Digital weight
    return 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;
}

SDL_Color hsvToRgb(HSV color)
{
    SDL_Color ret;
    double red;
    double green;
    double blue;
    double c = color.v * color.s;
    double huePrime = color.h / 60.0;
    double x = c * (1 - abs((fmod(huePrime, 2.0)) - 1));
    double m = color.v - c;
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

HSV rgbToHsv(SDL_Color color)
{
    HSV ret;
    double red = color.r / 255;
    double green = color.g / 255;
    double blue = color.b / 255;
    double min;
    double max;
    double delta;

    min = std::min(std::min(red, green), blue);
    max = std::max(std::max(red, green), blue);
    delta = max - min;
    ret.v = max;

    if(delta > 0)
    {
        if(max == red)
        {
            ret.h = 60 * fmod(((green - blue) / delta), 6.0);
        }else if(max == green){
            ret.h = 60 * ((blue - red) / delta) + 2;
        }else if(max == blue){
            ret.h = 60 * ((red - green) / delta) + 4;
        }

        if(max > 0)
        {
            ret.s = delta / max;
        }else{
            ret.s = 0;
        }
    }else{
        ret.h = 0;
        ret.s = 0;
    }

    if(ret.h < 0)
    {
        ret.h = 360 + ret.h;
    }

    return ret;
}


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
unsigned int getColor(unsigned int baseColor, unsigned int ambientColor, double reflectiveness, unsigned int i, unsigned int numColors)
{
    unsigned int diffA = abs((int)ambientColor - (int)baseColor);
    unsigned int diffB = std::min(baseColor, ambientColor) + (360 - std::max(baseColor, ambientColor));
    unsigned int diff = std::min(diffA, diffB);
    //Value to adjust how step of a curve we want range 0 - 2
    const double p = (1 - reflectiveness) * 2;

    //Solve for m
    double m = diff / std::pow((double)numColors, p);
    int newColor;

    if(diffA < diffB || baseColor > 360 / 2)
    {
        newColor = round((double)baseColor + (m * std::pow((double)i, p)));
    }else{
        newColor = round((double)baseColor - (m * std::pow((double)i, p)));
    }

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

/*************************************
*    |                               *
*  1 - - - - - - - - - X - - -       *
*    |                               *
*    |              X                *
*    |                               *
*    |          X                    *
*    |      X                        *
*  0 | X______________________       *
*      0    1   2   3   4  <----- i  *
*                                    *
*             y = mx^p               *
*************************************/
double getOffset(double p, double upperBound, unsigned int i, unsigned int numColors)
{
    //Solve for m
    double m = upperBound / std::pow((double)numColors - 1, p);
    return m * std::pow((double)i, p);
}
