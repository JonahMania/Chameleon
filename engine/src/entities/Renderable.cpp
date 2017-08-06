#include <iostream>
#include "../include/Renderable.hpp"

Renderable::Renderable()
{
    dest.x = 0;
    dest.y = 0;
    textureBounds.x = 0;
    textureBounds.y = 0;
}

bool Renderable::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, currentTexture, &textureBounds, &dest);
}

bool Renderable::setCurrentTexture(int name)
{
      std::map<int, SDL_Texture*>::iterator it;
      it = textures.find(name);
      if(it == textures.end())
      {
          std::cerr<<"Error: Texture with name '"<<name<<"' does not exist"<<std::endl;
          return false;
      }
      currentTexture = it->second;
      //Set texture bounds
      SDL_QueryTexture(currentTexture, NULL, NULL, &textureBounds.w, &textureBounds.h);
      dest.w = textureBounds.w;
      dest.h = textureBounds.h;
      return true;
}

bool Renderable::addTexture(int name, SDL_Texture* texture)
{
    if(!textures.insert(std::pair<int, SDL_Texture*>(name, texture)).second)
    {
        std::cerr<<"Error: Texture with name '"<<name<<"' already exists"<<std::endl;
        return false;
    }
    return true;
}

void Renderable::setRenderPosition(unsigned int x, unsigned int y)
{
    dest.x = x;
    dest.y = y;
}

void Renderable::freeAllTextures()
{
    for(auto& texture : textures)
    {
        if(texture.second != NULL)
        {
            SDL_DestroyTexture(texture.second);
        }
    }
    textures.clear();
}
