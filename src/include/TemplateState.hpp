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
        //Creates the state with a full image
        TemplateState(int n, std::string p, unsigned int scale = 1);
        /********************************************************
        * Creates the state with a specific tile from the sheet *
        * Assumes all tiles are of the same width and height    *
        * |--------------| Assumes all tiles are of the same    *                                       *
        * |  0 |  1 |  2 | width and height                     *
        * |--------------|                                      *
        * |  3 |  4 |  5 | i indicates the position of the tile *
        * |--------------| in the sprite sheet                  *
        ********************************************************/
        TemplateState(int n, std::string p, unsigned int w, unsigned int h, unsigned int i, int scale = 1);
        SDL_Surface* getTemplate();
        SDL_Rect* getBounds();
        std::string getPath();
        std::string getSurfaceId();
        static void freeTemplate(std::string p);
        static void freeAllTemplates();
        static std::map<std::string,SDL_Surface*> templates;
    protected:
        SDL_Surface* surface;
        SDL_Rect bounds;
    private:
        static SDL_Surface* getTemplate(std::string p, unsigned int scale);
        std::string path;
        std::string surfaceId;
};

#endif
