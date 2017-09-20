#include <iostream>
#include "../utils/colorUtils.hpp"
#include "../utils/pixelAccess.hpp"
#include "../include/Renderable.hpp"

Renderable::Renderable(Window* w, unsigned char r)
{
    dest.x = 0;
    dest.y = 0;
    renderMode = r;
    colorStateMachine = StateMachine<ColorState>();
    templateStateMachine = StateMachine<TemplateState>();
    window = w;
    texture = NULL;
}

void Renderable::addColorState(ColorState *state)
{
    if(colorStateMachine.addState(state) == 1)
    {
        //If this is the first state we are adding make texture
        generateTexture();
    }
}

void Renderable::addTemplateState(TemplateState *state)
{
    if(templateStateMachine.addState(state) == 1)
    {
        //If this is the first state we are adding make texture
        generateTexture();
    }
}

void Renderable::setColorState(int stateName)
{
    colorStateMachine.setCurrentState(stateName);
    //When state changes remake the texture
    generateTexture();
}

void Renderable::setTemplateState(int stateName)
{
    templateStateMachine.setCurrentState(stateName);
    //When state changes remake the texture
    generateTexture();
}

bool Renderable::render()
{
    SDL_RendererFlip flip;

    if(texture == NULL)
    {
        std::cerr<<"Error: Could not render texture is NULL"<<std::endl;
        return false;
    }
    //Make sure we want to render this sprite
    if((renderMode & SPRITE_NO_RENDER) != SPRITE_NO_RENDER)
    {
        //Check if this texture is on the screen if not don't render it
        if((dest.x + dest.w) > 0 && dest.x < window->getWidth()
            && (dest.y + dest.h) > 0 && dest.y < window->getHeight())
        {
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

            SDL_RenderCopyEx(window->getRenderer(), texture, &bounds, &dest, 0, NULL, flip);
        }
    }

    return true;
}

void Renderable::setRenderPosition(int x, int y)
{
    dest.x = x;
    dest.y = y;
}

void Renderable::setRenderMode(unsigned char r)
{
    renderMode = r;
}

bool Renderable::generateTexture()
{
    SDL_Color pixelColor;
    SDL_Surface* templateSurface;
    SDL_Surface* paintedSurface;
    std::map<SDL_Color, SDL_Color> colorMap;
    SDL_Texture* ret;
    SDL_Rect templateBounds;

    //Free old texture
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
    }
    texture = NULL;

    //If there is no template state make sure that our texture is NULL
    if(templateStateMachine.currentState == NULL)
    {
        return false;
    }

    templateBounds = templateStateMachine.currentState->getBounds();
    //Set bounds struct
    bounds = templateBounds;
    bounds.x = 0;
    bounds.y = 0;
    //Set the destination struct
    dest.w = bounds.w;
    dest.h = bounds.h;

    //Create a new texture
    if((templateSurface = templateStateMachine.currentState->getTemplate()) == NULL)
    {
        std::cerr<<"Error: Surface is NULL"<<std::endl;
        return false;
    }

    if(templateSurface == NULL)
    {
        std::cout<<"ITS NULL"<<std::endl;
    }

    paintedSurface = SDL_CreateRGBSurface(0, bounds.w, bounds.h, 32, 0, 0, 0, 0);
    if(paintedSurface == NULL)
    {
        std::cerr<<"Error: Surface is NULL "<<SDL_GetError()<<std::endl;
        return false;
    }

    SDL_BlitSurface(templateSurface, &templateBounds, paintedSurface, NULL);

    //If there is no color state just use the unpainted texture
    if(colorStateMachine.currentState == NULL)
    {
        texture = SDL_CreateTextureFromSurface(window->getRenderer(), paintedSurface);
        SDL_FreeSurface(paintedSurface);
        return true;
    }

    colorMap = colorStateMachine.currentState->generatePalette(templateStateMachine.currentState->getColorKeys());

    //Paint surface
    for(int i = 0; i < paintedSurface->w * paintedSurface->h; i++)
    {
        pixelColor = getPixel(paintedSurface, i);
        if(colorMap.find(pixelColor) != colorMap.end())
        {
            SDL_Color newPixelColor = colorMap.at(pixelColor);
            setPixel(paintedSurface, i, newPixelColor);
        }
    }
    texture = SDL_CreateTextureFromSurface(window->getRenderer(), paintedSurface);
    SDL_FreeSurface(paintedSurface);
    return true;
}

Renderable::~Renderable()
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
    }
}
