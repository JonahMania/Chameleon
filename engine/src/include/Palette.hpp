#ifndef _PALETTE_H_
#define _PALETTE_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <vector>
#include <math.h>

//Compare operator for SDL_Color so that std::map will work
bool operator<(const SDL_Color& a, const SDL_Color& b);

class Palette
{
    public:
        Palette();
        void setBaseColor(SDL_Color color);
        void setHighlightColor(SDL_Color color);
        void setAmbientColor(SDL_Color color);
        void setReflectivity(double r);
        void setIllumination(double i);
        void setHighlightMultiplyer(double hm);
        bool generatePalette(std::vector<SDL_Color> colorKeys);
        std::map<SDL_Color,SDL_Color> getColorMap();
    private:
        std::map<SDL_Color,SDL_Color> colorMap;
        SDL_Color baseColor;
        SDL_Color highlightColor;
        SDL_Color ambientColor;
        double reflectivity;
        double illumination;
        double highlightMultiplyer;
};

#endif
