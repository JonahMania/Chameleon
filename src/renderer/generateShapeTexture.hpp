#ifndef _GENERATESHAPETEXTURE_HPP_
#define _GENERATESHAPETEXTURE_HPP_

#include <SDL.h>
#include <iostream>

#include "../include/Shape.hpp"
#include "../utils/pixelAccess.hpp"

SDL_Texture* generateShapeTexture(Shape* shape, SDL_Renderer* windowRenderer);

#endif
