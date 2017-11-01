#include "generateShapeTexture.hpp"

bool inPolygon(std::vector<SDL_Point> points, int testX, int testY)
{
    int i;
    int j;
    bool ret = false;

    for (i = 0, j = points.size() - 1; i < points.size(); j = i++)
    {
        if(((points[i].y>testY) != (points[j].y>testY)) &&
            (testX < (points[j].x - points[i].x) *
            (testY - points[i].y) / (points[j].y - points[i].y) + points[i].x))
        {
            ret = !ret;
        }
    }
    return ret;
}

SDL_Texture* generateShapeTexture(Shape* shape, SDL_Renderer* windowRenderer)
{
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Color backgroundColor;

    backgroundColor.r = 0;
    backgroundColor.g = 0;
    backgroundColor.b = 0;
    backgroundColor.a = 255;

    if(shape->getNumPoints() < 3)
    {
        std::cerr<<"Error: Cannot create shape texture with less then 3 points"<<std::endl;
        return NULL;
    }

    surface = SDL_CreateRGBSurface(0, shape->getRenderWidth(), shape->getRenderHeight(), 32, 0, 0, 0, 0);
    if(surface == NULL)
    {
        std::cerr<<"Error: Could not create surface "<<SDL_GetError()<<std::endl;
        return NULL;
    }

    if(SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_ADD) != 0)
    {
        std::cerr<<"Error: Could not create surface "<<SDL_GetError()<<std::endl;
    }

    //Color surface
    for(unsigned int i = 0; i < surface->h; i++)
    {
        for(unsigned int j = 0; j < surface->w; j++)
        {
            if(inPolygon(shape->getPoints(), i, j))
            {
                setPixel(surface, (i * surface->w) + j, shape->getColor());
            }else{
                setPixel(surface, (i * surface->w) + j, backgroundColor);
            }
        }
    }

    texture = SDL_CreateTextureFromSurface(windowRenderer, surface);
    if(texture == NULL)
    {
        std::cerr<<"Error: Could not create texture "<<SDL_GetError()<<std::endl;
    }
    SDL_FreeSurface(surface);
    return texture;
}
