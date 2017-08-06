#ifndef _RENDERABLE_HPP_
#define _RENDERABLE_HPP_

#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "Entity.hpp"

class Renderable : public Entity
{
    public:
        Renderable();
        bool render(SDL_Renderer* renderer);
        void setRenderPosition(unsigned int x, unsigned int y);
        void freeAllTextures();
    protected:
        bool setCurrentTexture(int name);
        bool addTexture(int name, SDL_Texture* texture);
    private:
        SDL_Texture* currentTexture;
        std::map<int, SDL_Texture*> textures;
        SDL_Rect textureBounds;
        SDL_Rect dest;
};

#endif
