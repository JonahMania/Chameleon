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
        TemplateState(int n, std::string p, unsigned int scale = 1);
        SDL_Surface* getTemplate();
        SDL_Rect* getBounds();
        static void freeTemplate(std::string p);
        static void freeAllTemplates();
        static std::map<std::string,SDL_Surface*> templates;
    protected:
        SDL_Surface* surface;
        SDL_Rect bounds;
    private:
        static SDL_Surface* getTemplate(std::string p, unsigned int scale);
        std::string path;
};

#endif
