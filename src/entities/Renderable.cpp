#include <iostream>
#include "../include/Renderable.hpp"

Renderable::Renderable(unsigned char r)
{
    dest.x = 0;
    dest.y = 0;
    renderMode = r;
    renderStateMachine = StateMachine<RenderableState>();
    templateStateMachine = StateMachine<TemplateState>();
}

void Renderable::addRenderState(RenderableState *state)
{
    renderStateMachine.addState(state);
}

void Renderable::addTemplateState(TemplateState *state)
{
    templateStateMachine.addState(state);
}

void Renderable::setRenderState(int stateName)
{
    renderStateMachine.setCurrentState(stateName);
}

void Renderable::setTemplateState(int stateName)
{
    templateStateMachine.setCurrentState(stateName);
}

bool Renderable::render(Window window)
{
    SDL_Texture* temp;
    SDL_RendererFlip flip;
    //Make sure we want to render this sprite
    if((renderMode & SPRITE_NO_RENDER) != SPRITE_NO_RENDER)
    {
        //Create texture
        if(renderStateMachine.currentState == NULL)
        {
            temp = SDL_CreateTextureFromSurface(window.getRenderer(), templateStateMachine.currentState->getTemplate());
        }else{
            temp = renderStateMachine.currentState->newTexture(window.getRenderer(), templateStateMachine.currentState);
        }
        dest.w = templateStateMachine.currentState->getBounds()->w;
        dest.h = templateStateMachine.currentState->getBounds()->h;
        //Check if this tile is on the screen if not don't render it
        if((dest.x + dest.w) > 0 && dest.x < window.getWidth()
            && (dest.y + dest.h) > 0 && dest.y < window.getHeight())
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

            SDL_RenderCopyEx(window.getRenderer(), temp, templateStateMachine.currentState->getBounds(), &dest, 0, NULL, flip);
        }
        SDL_DestroyTexture(temp);
    }
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

Renderable::~Renderable()
{
    renderStateMachine.freeAllStates();
    templateStateMachine.freeAllStates();
}
