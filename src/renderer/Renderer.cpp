#include "paintSurface.hpp"
#include "../utils/colorUtils.hpp"
#include "../include/Renderer.hpp"

Renderer::Renderer(int w, int h)
{
    width = w;
    height = h;
    windowRect = {0, 0, width, height};
    textures = std::unordered_map<std::string, SDL_Texture*>();
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
    Sprite* sprite;
    Colorable* colorable;
    SDL_Surface* imageSurface;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect bounds;

    if(renderable == NULL)
    {
        return false;
    }
    //Check if we have a sprite
    sprite = dynamic_cast<Sprite*>(renderable);
    //If we don't have at least a sprite we cannot create a texture
    if(sprite == NULL)
    {
        return false;
    }
    //Check if we have a colorable or a renderable
    colorable = dynamic_cast<Colorable*>(renderable);

    //If the texture already exists dont remake it
    if(textures.find(sprite->getId()) != textures.end())
    {
        return true;
    }

    imageSurface = getSurface(sprite->getPath());
    if(imageSurface == NULL)
    {
        return false;
    }

    surface = SDL_CreateRGBSurface(0, sprite->getRenderWidth() * sprite->getScale(), sprite->getRenderHeight() * sprite->getScale(), 32, 0, 0, 0, 0);
    if(surface == NULL)
    {
        std::cerr<<"Error: Surface is NULL "<<SDL_GetError()<<std::endl;
        return false;
    }

    //Find the position of sprite sheet we want to use
    bounds.w = sprite->getRenderWidth();
    bounds.h = sprite->getRenderHeight();
    bounds.x = sprite->getSheetPositionX();
    bounds.y = sprite->getSheetPositionY();

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

    textures.insert(std::pair<std::string, SDL_Texture*>(sprite->getId(), texture));

    SDL_FreeSurface(surface);
    return true;
}

bool Renderer::render(Renderable* renderable)
{
    Sprite* sprite;
    SDL_Texture* texture;
    SDL_Rect dest;
    SDL_Rect bounds;
    std::unordered_map<std::string, SDL_Texture*>::const_iterator it;

    sprite = dynamic_cast<Sprite*>(renderable);

    dest.x = renderable->getRenderPositionX();
    dest.y = renderable->getRenderPositionY();
    dest.w = renderable->getRenderWidth();
    dest.h = renderable->getRenderHeight();
    //If we have a sprite multiply by scale
    if(sprite != NULL)
    {
        dest.w *= sprite->getScale();
        dest.h *= sprite->getScale();
    }
    //Check if this texture is on the screen if not don't render it
    if((dest.x + dest.w) < 0 || dest.x > width
    && (dest.y + dest.h) < 0 || dest.y > height)
    {
        return false;
    }

    (void)makeTexture(renderable);

    it = textures.find(renderable->getId());
    if(it == textures.end())
    {
        return false;
    }
    texture = it->second;

    if(texture == NULL)
    {
        return false;
    }

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
            std::cout<<"FREEING SURFACE "<<surface.first<<std::endl;
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
            std::cout<<"FREEING TEXTURE "<<texture.first<<std::endl;
            SDL_DestroyTexture(texture.second);
        }
    }
    textures.clear();
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
