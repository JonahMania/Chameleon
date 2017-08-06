#include "../include/Template.hpp"

Template::Template(unsigned int w, unsigned int h)
{
    templateSurface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    if(templateSurface == NULL)
    {
        std::cerr<<"Error: Could not create new surface "<<SDL_GetError()<<std::endl;
    }
}

Template::Template(Fragment fragment)
{
    //Get the fragment surface
    SDL_Surface *fragmentSurface = fragment.getSurface();
    if(fragmentSurface == NULL)
    {
        std::cerr<<"Error: Could not get fragment surface"<<std::endl;
        return;
    }
    //Create a new surface of the same size
    templateSurface = SDL_CreateRGBSurface(0, fragmentSurface->w, fragmentSurface->h, 32, 0, 0, 0, 0);
    if(templateSurface == NULL)
    {
        std::cerr<<"Error: Could not create new surface "<<SDL_GetError()<<std::endl;
        return;
    }
    //Blit the fragment to the new surface
    if(SDL_BlitSurface(fragmentSurface, NULL, templateSurface, NULL))
    {
        std::cerr<<"Error: Could not blit fragment to new surface "<<SDL_GetError()<<std::endl;
    }
}

bool Template::addFragment(Fragment fragment, int x, int y)
{
    SDL_Rect dest;
    //Get the fragment surface
    SDL_Surface *fragmentSurface = fragment.getSurface();
    if(fragmentSurface == NULL)
    {
        std::cerr<<"Error: Could not get fragment surface"<<std::endl;
        return false;
    }
    //Set the destination location and size
    dest.x = x;
    dest.y = y;
    dest.w = fragmentSurface->w;
    dest.h = fragmentSurface->h;
    //Blit the fragment to the template surface
    if(SDL_BlitSurface(fragmentSurface, NULL, templateSurface, &dest))
    {
        std::cerr<<"Error: Could not blit fragment to new surface "<<SDL_GetError()<<std::endl;
        return false;
    }
    return true;
}

bool Template::scaleTemplate(unsigned int scale)
{
    SDL_Rect dest;
    SDL_Surface *temp;

    if(templateSurface == NULL || scale < 2)
    {
        return false;
    }

    temp = SDL_CreateRGBSurface(0, templateSurface->w * scale,  templateSurface->h * scale, 32, 0, 0, 0, 0);
    if(temp == NULL)
    {
        std::cerr<<"Error: Could not create new surface "<<SDL_GetError()<<std::endl;
        return false;
    }
    //Set the destination location and size
    dest.x = 0;
    dest.y = 0;
    dest.w = templateSurface->w * scale;
    dest.h = templateSurface->h * scale;
    //Blit the fragment to the template surface
    if(SDL_BlitScaled(templateSurface, NULL, temp, &dest))
    {
        std::cerr<<"Error: Could not blit fragment to new surface "<<SDL_GetError()<<std::endl;
        return false;
    }

    SDL_FreeSurface(templateSurface);
    templateSurface = temp;

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
