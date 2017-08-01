#ifndef _PALETTE_H_
#define _PALETTE_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <algorithm>

//Compare operator for SDL_Color so that std::map will work
bool operator<(const SDL_Color& a, const SDL_Color& b);

class Palette
{
    public:
        Palette();
        void setHue(unsigned int h);
        void setAmbientColor(unsigned int ac);
        void setSaturation(double s);
        void setReflectiveness(double r);
        void setBrightness(double b);
        bool generatePalette(std::vector<SDL_Color> colorKeys);
        std::map<SDL_Color,SDL_Color> getColorMap();
    private:
        std::map<SDL_Color,SDL_Color> colorMap;
        unsigned int hue;
        unsigned int ambientColor;
        double saturation;
        double reflectiveness;
        double brightness;
};

#endif
