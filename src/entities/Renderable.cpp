#include <iostream>
#include "../utils/colorUtils.hpp"
#include "../utils/pixelAccess.hpp"
#include "../include/Renderable.hpp"

Renderable::Renderable(unsigned char r)
{
    dest.x = 0;
    dest.y = 0;
    renderMode = r;
    colorStateMachine = StateMachine<ColorState>();
    templateStateMachine = StateMachine<TemplateState>();
    texture = NULL;
    regenTexture = true;
}

void Renderable::addColorState(ColorState *state)
{
    colorStateMachine.addState(state);
}

void Renderable::addTemplateState(TemplateState *state)
{
    templateStateMachine.addState(state);
    if(templateStateMachine.currentState = state)
    {
        //If this is the current state set dest width and height to state
        dest.w = state->getBounds().w;
        dest.h = state->getBounds().h;
    }
}

void Renderable::setColorState(int stateName)
{
    colorStateMachine.setCurrentState(stateName);
    //If we change the template we must recreate the texture
    regenTexture = true;
}

void Renderable::setTemplateState(int stateName)
{
    templateStateMachine.setCurrentState(stateName);
    //Reset dest width and height to that of currentState
    dest.w = templateStateMachine.currentState->getBounds().w;
    dest.h = templateStateMachine.currentState->getBounds().h;
    //If we change the template we must recreate the texture
    regenTexture = true;
}

SDL_Texture* Renderable::getTexture(SDL_Renderer* renderer)
{
    //Check if we should regen this texture
    if(regenTexture)
    {
        generateTexture(renderer);
        regenTexture = false;
    }

    return texture;
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

int Renderable::getRenderMode()
{
    return renderMode;
}

bool Renderable::generateTexture(SDL_Renderer* renderer)
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
    bounds.w = templateBounds.w;
    bounds.h = templateBounds.h;
    bounds.x = 0;
    bounds.y = 0;

    //Create a new texture
    if((templateSurface = templateStateMachine.currentState->getTemplate()) == NULL)
    {
        std::cerr<<"Error: Surface is NULL"<<std::endl;
        return false;
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
        texture = SDL_CreateTextureFromSurface(renderer, paintedSurface);
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
    texture = SDL_CreateTextureFromSurface(renderer, paintedSurface);
    SDL_FreeSurface(paintedSurface);

    return true;
}

SDL_Rect Renderable::getDest()
{
    return dest;
}

SDL_Rect Renderable::getBounds()
{
    return bounds;
}

Renderable::~Renderable()
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
    }
}
