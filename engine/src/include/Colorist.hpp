#ifndef _COLORIST_HPP_
#define _COLORIST_HPP_

#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include <string>

//Class used to color pixel art templates
class Colorist
{
    public:
        Colorist();
        bool addPalette(std::string name, Palette* p);
        bool paintSurface(std::string paletteName, SDL_Surface *surface);
        bool pushColorKey(SDL_Color color);
    private:
        //All loaded palettes
        std::map<std::string,Palette*> palettes;
        //All color keys in order
        std::vector<SDL_Color> colorKeys;
};

#endif
