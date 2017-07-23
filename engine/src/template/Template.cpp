#include "../include/Template.hpp"

Template::Template(std::string path)
{
    templateSurface = IMG_Load(path.c_str());
    if(templateSurface == NULL)
    {
        std::cerr<<"Error: Could not load image at path '"<<path<<"' "<<IMG_GetError()<<std::endl;
    }
}

SDL_Surface *Template::getSurface()
{
    return templateSurface;
}

void Template::close()
{
    if(templateSurface != NULL)
    {
        SDL_FreeSurface(templateSurface);
    }
}
