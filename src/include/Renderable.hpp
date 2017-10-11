#ifndef _RENDERABLE_HPP_
#define _RENDERABLE_HPP_

#include <SDL.h>
#include <map>
#include <string>

#include "StateMachine.hpp"
#include "ColorState.hpp"
#include "TemplateState.hpp"

#define SPRITE_RENDER 0
#define SPRITE_NO_RENDER 1
#define SPRITE_FLIP_X 2
#define SPRITE_FLIP_Y 4

class Renderable
{
    public:
        Renderable(unsigned char r = SPRITE_RENDER);
        void addColorState(ColorState *state);
        void addTemplateState(TemplateState *state);
        void setColorState(int stateName);
        void setTemplateState(int stateName);
        // bool render(Window window);
        SDL_Texture* getTexture(SDL_Renderer* renderer);
        void setRenderPosition(int x, int y);
        void setRenderMode(unsigned char r);
        int getRenderMode();
        SDL_Rect getDest();
        SDL_Rect getBounds();
        virtual ~Renderable();
    private:
        bool generateTexture(SDL_Renderer* renderer);
        bool regenTexture;
        SDL_Texture* texture;
        unsigned char renderMode;
        StateMachine<ColorState> colorStateMachine;
        StateMachine<TemplateState> templateStateMachine;
        SDL_Rect dest;
        SDL_Rect bounds;
};

#endif
