#ifndef _COLORSTATE_HPP_
#define _COLORSTATE_HPP_

#include <SDL.h>
#include <iostream>
#include <vector>
#include <map>

#include "State.hpp"
#include "TemplateState.hpp"

class ColorState : public State
{
    public:
        ColorState(int n);
        void setHue(unsigned int h);
        void setAmbientColor(unsigned int ac);
        void setSaturation(double s);
        void setReflectiveness(double r);
        void setBrightness(double b);
        std::map<SDL_Color, SDL_Color> generatePalette(std::vector<SDL_Color> colorKeys);
        ~ColorState();
    private:
        unsigned int hue;
        unsigned int ambientColor;
        double saturation;
        double reflectiveness;
        double brightness;
};

#endif
