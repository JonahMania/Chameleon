#ifndef _RENDERABLESTATE_HPP_
#define _RENDERABLESTATE_HPP_

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "State.hpp"
#include "TemplateState.hpp"

class RenderableState : public State
{
    public:
        RenderableState(std::string n, std::vector<SDL_Color> c);
        void setHue(unsigned int h);
        void setAmbientColor(unsigned int ac);
        void setSaturation(double s);
        void setReflectiveness(double r);
        void setBrightness(double b);
        bool generatePalette();
        SDL_Texture* getTexture(SDL_Renderer* renderer, TemplateState* temp);
        ~RenderableState();
    private:
        std::map<std::string, SDL_Texture*> textures;
        std::map<SDL_Color, SDL_Color> colorMap;
        std::vector<SDL_Color> colorKeys;
        unsigned int hue;
        unsigned int ambientColor;
        double saturation;
        double reflectiveness;
        double brightness;
};

#endif