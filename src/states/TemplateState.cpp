#include "../include/TemplateState.hpp"

std::map<std::string,SDL_Surface*> TemplateState::templates = std::map<std::string,SDL_Surface*>();

TemplateState::TemplateState(int n, std::string p, unsigned int scale) : State(n)
{
    path = p;
    surface = TemplateState::getTemplate(path, scale);
    if(surface == NULL)
    {
        return;
    }
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = surface->w;
    bounds.h = surface->h;
}
TemplateState::TemplateState(int n, std::string p, unsigned int w, unsigned int h, unsigned int i, int scale) : State(n)
{
    unsigned int numXSprites;
    unsigned int numYSprites;
    unsigned int y;
    unsigned int x;
    path = p;
    surface = TemplateState::getTemplate(path, scale);
    if(surface == NULL)
    {
        return;
    }
    numXSprites = floor((double)surface->w / (double)(w * scale));
    numYSprites = floor((double)surface->h / (double)(h * scale));
    y = floor(i / numXSprites);
    x = i - (y * numXSprites);
    bounds.w = w * scale;
    bounds.h = h * scale;
    bounds.x = w * scale * x;
    bounds.y = h * scale * y;
}

SDL_Surface* TemplateState::getTemplate()
{
    return surface;
}

SDL_Rect* TemplateState::getBounds()
{
    return &bounds;
}

SDL_Surface* TemplateState::getTemplate(std::string p, unsigned int scale)
{
    std::map<std::string,SDL_Surface*>::iterator it;
    SDL_Surface* templateSurface;
    SDL_Surface* temp;
    SDL_Rect dest;
    //If surface already has been loaded
    it = templates.find(p);
    if(it != templates.end())
    {
        return it->second;
    }
    //If not attempt to load it
    temp = IMG_Load(p.c_str());
    if(temp == NULL)
    {
        std::cerr<<"Error: Could not load image at path '"<<p<<"' "<<IMG_GetError()<<std::endl;
        return NULL;
    }

    dest.x = 0;
    dest.y = 0;
    dest.w = temp->w * scale;
    dest.h = temp->h * scale;

    templateSurface = SDL_CreateRGBSurface(0, dest.w, dest.h, 32, 0, 0, 0, 0);
    if(SDL_BlitScaled(temp, NULL, templateSurface, &dest))
    {
        std::cerr<<"Error: Could not blit fragment to new surface "<<SDL_GetError()<<std::endl;
        SDL_FreeSurface(temp);
        return NULL;
    }

    SDL_FreeSurface(temp);

    //Insert new surface into map
    templates.insert(std::pair<std::string,SDL_Surface*>(p, templateSurface));

    //Return new surface
    return templateSurface;
}

void TemplateState::freeTemplate(std::string p)
{
    std::map<std::string,SDL_Surface*>::iterator it;

    it = templates.find(p);
    if(it != templates.end())
    {
        if(it->second != NULL)
        {
            SDL_FreeSurface(it->second);
        }
        templates.erase(it);
    }
}

void TemplateState::freeAllTemplates()
{
    for(auto& temp : templates)
    {
        if(temp.second != NULL)
        {
            SDL_FreeSurface(temp.second);
        }
    }
    templates.clear();
}
