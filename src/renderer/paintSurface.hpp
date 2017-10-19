#ifndef _PAINTSURFACE_HPP_
#define _PAINTSURFACE_HPP_

#include <SDL.h>
#include <set>

#include "../include/Colorable.hpp"
#include "../utils/colorUtils.hpp"

bool paintSurface(SDL_Surface* surface, Colorable colorable, std::set<SDL_Color> colorKeys);

#endif
