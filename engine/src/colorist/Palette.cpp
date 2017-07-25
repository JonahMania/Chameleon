#include <algorithm>

#include "../utils/colorNormal.hpp"
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

Palette::Palette()
{
    baseColor.r = 255;
    baseColor.g = 255;
    baseColor.b = 255;

    highlightColor.r = 255;
    highlightColor.g = 255;
    highlightColor.b = 255;

    ambientColor.r = 255;
    ambientColor.g = 255;
    ambientColor.b = 255;

    reflectivity = 0;
    illumination = 1;
    highlightMultiplyer = 1;
}

void Palette::setBaseColor(SDL_Color color)
{
    baseColor = color;
}

void Palette::setHighlightColor(SDL_Color color)
{
    highlightColor = color;
}

void Palette::setAmbientColor(SDL_Color color)
{
    ambientColor = color;
}

void Palette::setReflectivity(double r)
{
    reflectivity = r;
}

void Palette::setIllumination(double i)
{
    illumination = i;
}

void Palette::setHighlightMultiplyer(double hm)
{
    highlightMultiplyer = hm;
}

bool Palette::generatePalette(std::vector<SDL_Color> colorKeys)
{
    unsigned int numColors = colorKeys.size();
    std::vector<SDL_Color> newPalette;

    ColorNormal highlightColorNorm = ColorNormal(highlightColor);
    double weight;
    ColorNormal light;
    ColorNormal currColor;

    if(numColors <= 0)
    {
        return false;
    }
    colorMap.clear();

    for(int i = 0; i < numColors; i++)
    {
        //Create a normilized weight for each color in palette
        weight = pow(i / (double)(numColors - 1), illumination);
        //Calculate highlightColor considering the highlight multiplyer
        highlightColorNorm = highlightColorNorm * highlightMultiplyer;
        //Create lighting color
        ColorNormal light = (ColorNormal(ambientColor) * weight) + (highlightColorNorm * (1 - weight));
        //Offset base color by lighting
        currColor = ColorNormal(baseColor) * light;
        //Apply reflectivity
        currColor = (light * reflectivity) + (currColor * (1 - reflectivity));
        newPalette.push_back(currColor.toSDL_Color());
    }

    //Sort both sets of colors by brightness before creating map
    std::sort(colorKeys.begin(), colorKeys.end(), luminanceSort());
    std::sort(newPalette.begin(), newPalette.end(), luminanceSort());
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
