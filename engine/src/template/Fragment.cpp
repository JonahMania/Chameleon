#include "../include/Fragment.hpp"

Fragment::Fragment(std::string path)
{
    fragmentSurface = IMG_Load(path.c_str());
    if(fragmentSurface == NULL)
    {
        std::cerr<<"Error: Could not load image at path '"<<path<<"' "<<IMG_GetError()<<std::endl;
    }
}

SDL_Surface *Fragment::getSurface()
{
    return fragmentSurface;
}

void Fragment::close()
{
    if(fragmentSurface != NULL)
    {
        SDL_FreeSurface(fragmentSurface);
    }
}
