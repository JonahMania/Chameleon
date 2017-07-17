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
    Uint32 *pixels = (Uint32 *)surface->pixels;
    SDL_Color pixelColor;    
  
    if(surface == NULL)
    {
        return false;
    }
    if(palettes.find(paletteName) == palettes.end())
    {
        std::cerr<<"Error: Palette '"<<paletteName<<"' does not exist"<<std::endl;
        return false;
    }
    Palette *palette = palettes.at(paletteName);
    palette->generatePalette(colorKeys);
    for(int i = 0; i < surface->w * surface->h; i++)
    {
        SDL_GetRGB(pixels[i*surface->w], surface->format, &pixelColor.r, &pixelColor.g, &pixelColor.b);        
    }

    return true;
}

bool Colorist::pushColorKey(SDL_Color color)
{
    colorKeys.push_back(color);
}
