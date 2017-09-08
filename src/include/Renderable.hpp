#ifndef _RENDERABLE_HPP_
#define _RENDERABLE_HPP_

#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "StateMachine.hpp"
#include "RenderableState.hpp"
#include "TemplateState.hpp"
#include "Window.hpp"

#define SPRITE_RENDER 0
#define SPRITE_NO_RENDER 1
#define SPRITE_FLIP_X 2
#define SPRITE_FLIP_Y 4

class Renderable
{
    public:
        Renderable(unsigned char r = SPRITE_RENDER);
        void addRenderState(RenderableState *state);
        void addTemplateState(TemplateState *state);
        void setRenderState(int stateName);
        void setTemplateState(int stateName);
        bool render(Window window);
        void setRenderPosition(unsigned int x, unsigned int y);
        void setRenderMode(unsigned char r);
        virtual ~Renderable();
    private:
        unsigned char renderMode;
        StateMachine<RenderableState> renderStateMachine;
        StateMachine<TemplateState> templateStateMachine;
    protected:
        SDL_Rect dest;

};

#endif
