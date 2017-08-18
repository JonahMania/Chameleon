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

bool Renderable::render(Window window)
{
    //Create texture
    SDL_Texture* temp = renderStateMachine.currentState->getTexture(window.getRenderer(), templateStateMachine.currentState);
    dest.w = templateStateMachine.currentState->getBounds()->w;
    dest.h = templateStateMachine.currentState->getBounds()->h;
    window.render(temp, templateStateMachine.currentState->getBounds(), &dest);
}
