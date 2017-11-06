#ifndef _GENERATESHAPETEXTURE_HPP_
#define _GENERATESHAPETEXTURE_HPP_

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include <iostream>

#include "../include/Shape.hpp"
#include "../utils/pixelAccess.hpp"

GLuint surfaceToTexture(SDL_Surface* surface);
GLuint generateShapeTexture(Shape* shape);

#endif
