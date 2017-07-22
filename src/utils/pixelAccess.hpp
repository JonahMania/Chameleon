#ifndef _PIXELACCESS_HPP_
#define _PIXELACCESS_HPP_

#include <SDL2/SDL.h>
#include <iostream>

SDL_Color getPixel(SDL_Surface *surface, int i);
void setPixel(SDL_Surface *surface, int i, SDL_Color pixel);

#endif
