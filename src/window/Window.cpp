#include "../include/Window.hpp"

Window::Window(int w, int h)
{
    width = w;
    height = h;
    windowRect = {0, 0, width, height};
}

bool Window::initialize()
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

int Window::getHeight()
{
    return height;
}

int Window::getWidth()
{
    return width;
}

bool Window::clear()
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

void Window::update()
{
    SDL_RenderPresent(windowRenderer);
}

void Window::render(Renderable* renderable)
{
    SDL_RendererFlip flip;
    int renderMode = renderable->getRenderMode();
    SDL_Rect dest = renderable->getDest();
    SDL_Rect bounds;
    SDL_Texture* texture;

    //Make sure we want to render this sprite
    if((renderMode & SPRITE_NO_RENDER) != SPRITE_NO_RENDER)
    {
        //Check if this texture is on the screen if not don't render it
        if((dest.x + dest.w) > 0 && dest.x < width
            && (dest.y + dest.h) > 0 && dest.y < height)
        {
            //Make sure we get the texture only if the renderable is on screen
            //to avoid unnecessary updates
            texture = renderable->getTexture(windowRenderer);
            if(texture ==  NULL)
            {
                return;
            }
            bounds = renderable->getBounds();

            flip = SDL_FLIP_NONE;
            if((renderMode & SPRITE_FLIP_X) == SPRITE_FLIP_X)
            {
                flip = SDL_FLIP_VERTICAL;
            }
            if((renderMode & SPRITE_FLIP_Y) == SPRITE_FLIP_Y)
            {
                flip = SDL_FLIP_HORIZONTAL;
            }
            if((renderMode & (SPRITE_FLIP_X | SPRITE_FLIP_Y)) == (SPRITE_FLIP_X | SPRITE_FLIP_Y))
            {
                flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
            }
            SDL_RenderCopyEx(windowRenderer, texture, &bounds, &dest, 0, NULL, flip);
        }
    }
}

void Window::render(std::vector<Renderable*> renderables)
{
    for(auto renderable : renderables)
    {
        render(renderable);
    }
}

void Window::close()
{
    SDL_DestroyRenderer(windowRenderer);
    SDL_DestroyWindow(window);
    windowRenderer = NULL;
    window = NULL;
    SDL_Quit();
}
