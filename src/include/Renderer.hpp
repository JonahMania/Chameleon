#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#define GL_GLEXT_PROTOTYPES

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

#include "Renderable.hpp"
#include "Colorable.hpp"
#include "MaskShader.hpp"
#include "BasicShader.hpp"

#define MAX_LAYERS 8

class Renderer
{
    public:
        Renderer(int w, int h, unsigned int l=MAX_LAYERS);
        bool initialize();
        GLuint makeTexture(Renderable* renderable);
        bool render(Renderable* renderable);
        //Clear the screen to black
        bool clear();
        //Update the latest changes to the screen
        void update();
        void enableRenderCache();
        void disableRenderCache();
        bool freeAllSurfaces();
        bool freeAllTextures();
        bool freeAll();
        ~Renderer();
    private:
        //Dimensions of the window
        int width;
        int height;
        //Flag to tell if textures should be cached or not
        bool useRenderCache;
        unsigned int numLayers;
        SDL_GLContext context;
        SDL_Window* window;
        SDL_Rect windowRect;
        SDL_Surface* getSurface(std::string path);
        std::unordered_map<std::string, std::set<SDL_Color>> colorKeys;
        std::unordered_map<std::string, SDL_Surface*> surfaces;
        std::unordered_map<std::string, GLuint> textures;
        //Array of frame buffer objects one for each layer
        GLuint *layerFrameBuffers;
        //Array of textures to attach to each frame buffer
        GLuint *layerTextures;
        //Shaders
        BasicShader basicShader;
        MaskShader maskShader;
};

#endif
