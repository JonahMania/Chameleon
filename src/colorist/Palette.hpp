#ifndef _PALETTE_H_
#define _PALETTE_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <vector>

//Compare operator for SDL_Color so that std::map will work
bool operator<(const SDL_Color& a, const SDL_Color& b);

class Palette
{
    public:
        Palette();
        Palette(Uint8 r, Uint8 g, Uint8 b);
        bool generatePalette(std::vector<SDL_Color> colorKeys);
        std::map<SDL_Color,SDL_Color> getColorMap();
    private:
        std::map<SDL_Color,SDL_Color> colorMap;
        SDL_Color baseColor;

};

#endif
