#include <algorithm>

#include "../utils/colorUtils.hpp"
#include "../include/Palette.hpp"

//Compare operator for SDL_Color so that std::map will work
bool operator<(const SDL_Color& a, const SDL_Color& b)
{
    return luminance(a) < luminance(b);
}
//Custom compare used to sort colors
struct luminanceSort
{
    inline bool operator()(const SDL_Color& a, const SDL_Color& b)
    {
        return luminance(a) < luminance(b);
    }
};

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

Palette::Palette()
{
    hue = 0;
    ambientColor = 0;
    saturation = 0;
    reflectiveness = 0.5;
    brightness = 0.5;
}

void Palette::setHue(unsigned int h)
{
    if(h > 360)
    {
        hue = 360;
    }else{
        hue = h;
    }
}

void Palette::setAmbientColor(unsigned int ac)
{
    if(ac > 360)
    {
        ambientColor = 360;
    }else{
        ambientColor = ac;
    }
}

void Palette::setSaturation(double s)
{
    if(s > 1)
    {
        saturation = 1;
    }else{
        saturation = s;
    }
}

void Palette::setReflectiveness(double r)
{
    if(r < 0)
    {
        reflectiveness = 0;
    }else if(r > 1){
        reflectiveness = 1;
    }else{
        reflectiveness = r;
    }
}

void Palette::setBrightness(double b)
{
    if(b > 1)
    {
        brightness = 1;
    }else if(b < 0){
        brightness = 0;
    }else{
        brightness = b;
    }
}

bool Palette::generatePalette(std::vector<SDL_Color> colorKeys)
{
    unsigned int numColors = colorKeys.size();
    std::vector<SDL_Color> newPalette;
    unsigned int newColor;

    if(numColors <= 0)
    {
        return false;
    }
    colorMap.clear();

    for(unsigned int i = 0; i < numColors; i++)
    {
        newColor = getColor(hue, ambientColor, reflectiveness, i, numColors);
        newPalette.push_back(hsvToRgb(HSV(newColor, getOffset(1 - saturation, 1, i, numColors), getOffset(1 - brightness, brightness * 2, i, numColors))));
    }

    //Sort colr keys by brightness before creating map
    std::sort(colorKeys.begin(), colorKeys.end(), luminanceSort());

    //Create mapping
    for(int i = 0; i < numColors; i++)
    {
        colorMap.insert(std::pair<SDL_Color,SDL_Color>(colorKeys.at(i), newPalette.at(i)));
    }

    return true;
}

std::map<SDL_Color,SDL_Color> Palette::getColorMap()
{
    return colorMap;
}
