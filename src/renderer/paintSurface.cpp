#include "paintSurface.hpp"

std::map<SDL_Color, SDL_Color> createColorMap(std::set<SDL_Color> colorKeys, Colorable colorable)
{
    unsigned int numColors = colorKeys.size();
    double newColor;
    SDL_Color paletteColor;
    std::map<SDL_Color, SDL_Color> colorMap = std::map<SDL_Color, SDL_Color>();
    unsigned int colorIndex = 0;
    double lowerBound = 0;
    double upperBound = 0;

    if(numColors <= 0)
    {
        return colorMap;
    }

    for(auto colorKey : colorKeys)
    {
        newColor = getColor(colorable.getHue(), colorable.getStep(), colorIndex);
        lowerBound = colorable.getBrightness() - colorable.getReflectiveness() * colorable.getBrightness();
        upperBound = colorable.getBrightness() + colorable.getReflectiveness() * (1 - colorable.getBrightness());
        HSL tmp = HSL(newColor, colorable.getSaturation(),
            getOffset((1 - colorable.getReflectiveness()) * 2, lowerBound, upperBound, colorIndex, numColors));
        paletteColor = hslToRgb(tmp);
        colorMap.insert(std::pair<SDL_Color,SDL_Color>(colorKey, paletteColor));
        colorIndex++;
    }

    return colorMap;
}

bool paintSurface(SDL_Surface* surface, Colorable colorable, std::set<SDL_Color> colorKeys)
{
    std::map<SDL_Color, SDL_Color> colorMap;
    SDL_Color pixelColor;

    colorMap = createColorMap(colorKeys, colorable);
    //Paint surface
    for(int i = 0; i < surface->w * surface->h; i++)
    {
        pixelColor = getPixel(surface, i);
        if(colorMap.find(pixelColor) != colorMap.end())
        {
            setPixel(surface, i, colorMap.at(pixelColor));
        }
    }
}
