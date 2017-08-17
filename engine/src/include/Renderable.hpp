#ifndef _RENDERABLE_HPP_
#define _RENDERABLE_HPP_

#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "StateMachine.hpp"
#include "RenderableState.hpp"
#include "TemplateState.hpp"

class Renderable
{
    public:
        Renderable();
        StateMachine<RenderableState> renderStateMachine;
        StateMachine<TemplateState> templateStateMachine;
        void freeAllStates();
        bool render(SDL_Renderer* renderer);
        void setRenderPosition(unsigned int x, unsigned int y);
    private:
        SDL_Rect dest;
};

#endif
