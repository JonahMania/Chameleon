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
        bool addPalette(std::string name, Palette p);
        bool paintSurface(std::string paletteName, SDL_Surface *surface);
        bool pushColorKey(SDL_Color color);
        //Creates a sample of a surface with all palettes in the Colorist
        //Returned surfaced must be freed using SDL_FreeSurface
        SDL_Surface *createSample(SDL_Surface *surface, unsigned int w, unsigned int h);
    private:
        //All loaded palettes
        std::map<std::string,Palette> palettes;
        //All color keys in order
        std::vector<SDL_Color> colorKeys;
};

#endif
