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

void Window::render(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dest)
{
    SDL_RenderCopy(windowRenderer, texture, src, dest);
}

SDL_Renderer* Window::getRenderer()
{
    return windowRenderer;
}

void Window::close()
{
    SDL_DestroyRenderer(windowRenderer);
    SDL_DestroyWindow(window);
    windowRenderer = NULL;
    window = NULL;
    SDL_Quit();
}
