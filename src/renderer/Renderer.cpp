#include "paintSurface.hpp"
#include "../utils/colorUtils.hpp"
#include "../include/Renderer.hpp"

Renderer::Renderer(int w, int h)
{
    width = w;
    height = h;
    windowRect = {0, 0, width, height};
    textures = std::unordered_map<Renderable, SDL_Texture*>();
}

bool Renderer::initialize()
{
    //Initialize SDL library
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "ERROR: SDL could not initialize " << SDL_GetError() << std::endl;
        return false;
    }
    //Create window
    window = SDL_CreateWindow("colorGen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        std::cerr << "ERROR: Window was not created " << SDL_GetError() << std::endl;
        return false;
    }
    //Create rendering context for window
    windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(windowRenderer == NULL)
    {
        std::cerr << "ERROR: renderer cound not be created " << SDL_GetError() << std::endl;
        return false;
    }
    //Initilize PNG loading
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "ERROR: PNG loading was not initilized " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Surface* Renderer::getSurface(std::string path)
{
    std::unordered_map<std::string, SDL_Surface*>::const_iterator it;
    SDL_Surface* surface;

    //Check if we have the surface in cache
    it = surfaces.find(path);
    if(it != surfaces.end())
    {
        return it->second;
    }
    //If the surface does not exist create it
    surface = IMG_Load(path.c_str());
    if(surface == NULL)
    {
        std::cerr<<"Error: Could not load surface at path '"<<path<<"' "<<IMG_GetError()<<std::endl;
        return NULL;
    }

    //Get color keys from surface and insert them into the map
    colorKeys.insert(std::pair<std::string, std::set<SDL_Color>>(path, getColorKeys(surface)));
    //Add new surface to cache
    surfaces.insert(std::pair<std::string, SDL_Surface*>(path, surface));
    return surface;
}

bool Renderer::makeTexture(Renderable* renderable)
{
    Colorable* colorable;
    SDL_Surface* imageSurface;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect bounds;

    if(renderable == NULL)
    {
        return false;
    }
    //Check if we have a colorable or a renderable
    colorable = dynamic_cast<Colorable*>(renderable);

    //If the texture already exists dont remake it
    if(!colorable && textures.find(*renderable) != textures.end())
    {
        return true;
    }
    if(colorable && coloredTextures.find(*colorable) != coloredTextures.end())
    {
        return true;
    }

    imageSurface = getSurface(renderable->getPath());
    if(imageSurface == NULL)
    {
        return false;
    }

    surface = SDL_CreateRGBSurface(0, renderable->getRenderWidth() * renderable->getScale(), renderable->getRenderHeight() * renderable->getScale(), 32, 0, 0, 0, 0);
    if(surface == NULL)
    {
        std::cerr<<"Error: Surface is NULL "<<SDL_GetError()<<std::endl;
        return false;
    }

    //Find the position of sprite sheet we want to use
    bounds.w = renderable->getRenderWidth();
    bounds.h = renderable->getRenderHeight();
    bounds.x = renderable->getSheetPositionX();
    bounds.y = renderable->getSheetPositionY();

    if(SDL_BlitScaled(imageSurface, &bounds, surface, NULL) < 0)
    {
        std::cerr<<"Error: Could not blit surface "<<SDL_GetError()<<std::endl;
        SDL_FreeSurface(surface);
        return false;
    }

    if(colorable)
    {
        (void)paintSurface(surface, *colorable, colorKeys[colorable->getPath()]);
    }

    texture = SDL_CreateTextureFromSurface(windowRenderer, surface);

    if(texture == NULL)
    {
        SDL_FreeSurface(surface);
        return false;
    }

    if(colorable)
    {
        coloredTextures.insert(std::pair<Colorable, SDL_Texture*>(*colorable, texture));
    }else{
        textures.insert(std::pair<Renderable, SDL_Texture*>(*renderable, texture));
    }
    SDL_FreeSurface(surface);
    return true;
}

bool Renderer::render(Renderable* renderable)
{
    Colorable* colorable;
    SDL_Texture* texture;
    SDL_Rect dest;
    SDL_Rect bounds;
    std::unordered_map<Renderable, SDL_Texture*>::const_iterator rit;
    std::unordered_map<Colorable, SDL_Texture*>::const_iterator cit;

    (void)makeTexture(renderable);

    //Check if we have a colorable or a renderable
    colorable = dynamic_cast<Colorable*>(renderable);

    if(colorable)
    {
        cit = coloredTextures.find(*colorable);
        if(cit == coloredTextures.end())
        {
            return false;
        }
        texture = cit->second;
    }else{
        rit = textures.find(*renderable);
        if(rit == textures.end())
        {
            return false;
        }
        texture = rit->second;
    }


    if(texture == NULL)
    {
        return false;
    }

    dest.x = renderable->getRenderPositionX();
    dest.y = renderable->getRenderPositionY();
    dest.w = renderable->getRenderWidth() * renderable->getScale();
    dest.h = renderable->getRenderHeight() * renderable->getScale();

    bounds.x = 0;
    bounds.y = 0;
    bounds.w = dest.w;
    bounds.h = dest.h;

    SDL_RenderCopyEx(windowRenderer, texture, &bounds, &dest, 0, NULL, SDL_FLIP_NONE);
}

bool Renderer::clear()
{
    if(SDL_SetRenderDrawColor(windowRenderer, 0, 0, 0, 0xFF) != 0)
    {
        return false;
    }
    if(SDL_RenderClear(windowRenderer) != 0)
    {
        return false;
    }
    return true;
}

void Renderer::update()
{
    SDL_RenderPresent(windowRenderer);
}

bool Renderer::freeAllSurfaces()
{
    for(auto &surface : surfaces)
    {
        if(surface.second)
        {
            std::cout<<"FREEING SURFACE"<<std::endl;
            SDL_FreeSurface(surface.second);
        }
    }
    surfaces.clear();
}

bool Renderer::freeAllTextures()
{
    for(auto &texture : textures)
    {
        if(texture.second)
        {
            std::cout<<"FREEING TEXTURE"<<std::endl;
            SDL_DestroyTexture(texture.second);
        }
    }
    textures.clear();
    for(auto &coloredTexture : coloredTextures)
    {
        if(coloredTexture.second)
        {
            std::cout<<"FREEING COLORED TEXTURE"<<std::endl;
            SDL_DestroyTexture(coloredTexture.second);
        }
    }
    coloredTextures.clear();
}

bool Renderer::freeAll()
{
    return freeAllTextures() && freeAllSurfaces();
}

Renderer::~Renderer()
{
    std::cout<<"FREEING RENDERER"<<std::endl;
    freeAll();
    SDL_DestroyRenderer(windowRenderer);
    windowRenderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
}
