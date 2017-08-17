#ifndef _TEMPLATESTATE_HPP_
#define _TEMPLATESTATE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <map>

#include "State.hpp"

class TemplateState : public State
{
    public:
        TemplateState(std::string n, std::string p, unsigned int scale = 1);
        SDL_Surface* getTemplate();
        SDL_Rect* getBounds();
        static void freeTemplate(std::string p);
        static void freeAllTemplates();
        static std::map<std::string,SDL_Surface*> templates;
    private:
        static SDL_Surface* getTemplate(std::string p, unsigned int scale);
        SDL_Surface* surface;
        std::string path;
        SDL_Rect bounds;
};

#endif
