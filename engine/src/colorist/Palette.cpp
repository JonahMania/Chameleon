#include "../include/Palette.hpp"

//Compare operator for SDL_Color so that std::map will work
bool operator<(const SDL_Color& a, const SDL_Color& b)
{
    return a.r + a.g + a.b < b.r + b.g + b.b;
}

Palette::Palette()
{
    this->baseColor.r = 255;
    this->baseColor.g = 255;
    this->baseColor.b = 255;
}

Palette::Palette(Uint8 r, Uint8 g, Uint8 b)
{
    this->baseColor.r = r;
    this->baseColor.g = g;
    this->baseColor.b = b;
}

bool Palette::generatePalette(std::vector<SDL_Color> colorKeys)
{
    unsigned int numColors = colorKeys.size();
    if(numColors <= 0)
    {
        return false;
    }
    colorMap.clear();
    for(SDL_Color colorKey : colorKeys)
    {
        colorMap.insert(std::pair<SDL_Color,SDL_Color>(colorKey,SDL_Color({r:255,g:255,b:255})));
    }
    return true;
}

std::map<SDL_Color,SDL_Color> Palette::getColorMap()
{
    return colorMap;
}
