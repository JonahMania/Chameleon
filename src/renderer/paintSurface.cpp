#include "paintSurface.hpp"

std::map<SDL_Color, SDL_Color> createColorMap(std::set<SDL_Color> colorKeys, Colorable colorable)
{
    unsigned int numColors = colorKeys.size();
    unsigned int newColor;
    SDL_Color paletteColor;
    std::map<SDL_Color, SDL_Color> colorMap = std::map<SDL_Color, SDL_Color>();
    unsigned int colorIndex = 0;

    if(numColors <= 0)
    {
        return colorMap;
    }

    for(auto colorKey : colorKeys)
    {
        newColor = getColor(colorable.getHue(), colorable.getAmbientColor(), colorable.getReflectiveness(), colorIndex, numColors);
        paletteColor = hsvToRgb(HSV(newColor,
            getOffset(1 - colorable.getSaturation(), 1, colorIndex, numColors),
            getOffset(1 - colorable.getBrightness(), colorable.getBrightness() * 2, colorIndex, numColors)));
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
