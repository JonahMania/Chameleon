#ifndef _COLORIST_HPP_
#define _COLORIST_HPP_

#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include <string>

#include "Template.hpp"
#include "Palette.hpp"

//Class used to color pixel art templates
class Colorist
{
    public:
        Colorist();
        bool addPalette(std::string name, Palette p);
        bool pushColorKey(SDL_Color color);
        //Creates a new surface from a template  and a pallete
        //Returned surface must be freed SDL_DestroyTexture
        SDL_Texture *createTexture(Template temp, std::string paletteName, SDL_Renderer* renderer);
        //Creates a sample of a surface with all palettes in the Colorist
        //Returned surfaced must be freed using SDL_FreeSurface
        SDL_Surface *createSample(SDL_Surface *surface, unsigned int w, unsigned int h);
    private:
        bool paintSurface(std::string paletteName, SDL_Surface *surface);
        //All loaded palettes
        std::map<std::string,Palette> palettes;
        //All color keys in order
        std::vector<SDL_Color> colorKeys;
};

#endif
