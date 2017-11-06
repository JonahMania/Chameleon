#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

#include "Renderable.hpp"
#include "Colorable.hpp"

class Renderer
{
    public:
        Renderer(int w, int h);
        bool initialize();
        bool makeTexture(Renderable* renderable);
        bool render(Renderable* renderable);
        //Clear the screen to black
        bool clear();
        //Update the latest changes to the screen
        void update();
        bool freeAllSurfaces();
        bool freeAllTextures();
        bool freeAll();
        ~Renderer();
    private:
        //Dimensions of the window
        int width;
        int height;
        SDL_GLContext context;
        SDL_Window* window;
        SDL_Rect windowRect;
        SDL_Surface* getSurface(std::string path);
        std::unordered_map<std::string, std::set<SDL_Color>> colorKeys;
        std::unordered_map<std::string, SDL_Surface*> surfaces;
        std::unordered_map<std::string, GLuint> textures;
};

#endif
