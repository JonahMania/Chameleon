#include "Colorist.hpp"

Colorist::Colorist()
{

}

bool Colorist::addPalette(std::string name, Palette* p)
{
    if(p == NULL)
    {
        return false;
    }

    if(palettes.find(name) != palettes.end())
    {
        return false;
    }

    palettes.insert(std::pair<std::string,Palette*>(name, p));

    return true;
}

bool Colorist::paintSurface(std::string paletteName, SDL_Surface *surface)
{
    SDL_Color pixelColor;
    Palette *palette;
    std::map<SDL_Color,SDL_Color> colorMap;

    if(surface == NULL)
    {
        std::cerr<<"Error: Passing NULL surface"<<std::endl;
        return false;
    }
    //Make sure our palette exists
    if(palettes.find(paletteName) == palettes.end())
    {
        std::cerr<<"Error: Palette '"<<paletteName<<"' does not exist"<<std::endl;
        return false;
    }
    //Get palette and color map
    palette = palettes.at(paletteName);
    palette->generatePalette(colorKeys);
    colorMap = palette->getColorMap();

    for(int i = 0; i < surface->w * surface->h; i++)
    {
        pixelColor = getPixel(surface, i);
        if(colorMap.find(pixelColor) != colorMap.end())
        {
            SDL_Color newPixelColor = colorMap.at(pixelColor);
            setPixel(surface, i, newPixelColor);
        }
    }

    return true;
}

bool Colorist::pushColorKey(SDL_Color color)
{
    //Make sure alpha is set to 0
    color.a = 0;
    colorKeys.push_back(color);
}
