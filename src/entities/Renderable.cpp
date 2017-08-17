#include <iostream>
#include "../include/Renderable.hpp"

Renderable::Renderable()
{
    dest.x = 0;
    dest.y = 0;

    renderStateMachine = StateMachine<RenderableState>();
    templateStateMachine = StateMachine<TemplateState>();
}

void Renderable::freeAllStates()
{
    renderStateMachine.freeAllStates();
    templateStateMachine.freeAllStates();
}

bool Renderable::render(SDL_Renderer* renderer)
{
    //Create texture
    SDL_Texture* temp = renderStateMachine.currentState->getTexture(renderer, templateStateMachine.currentState);
    dest.w = templateStateMachine.currentState->getTemplate()->w;
    dest.h = templateStateMachine.currentState->getTemplate()->h;
    SDL_RenderCopy(renderer, temp, templateStateMachine.currentState->getBounds(), &dest);
}
