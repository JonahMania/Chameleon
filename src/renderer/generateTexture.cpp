#include "generateTexture.hpp"

GLuint surfaceToTexture(SDL_Surface* surface)
{
    GLuint texture;
    int mode;

    glGenTextures(1, &texture);

    if(texture < 1)
    {
        std::cout<<"Error: Could not create texture "<<glGetError()<<std::endl;
        return 0;
    }

    mode = GL_RGB;
    if(surface->format->BytesPerPixel == 4)
    {
        if(surface->format->Rmask == 0x000000ff)
        {
            mode = GL_RGBA;
        }else{
            mode = GL_BGRA;
        }
    }else if(surface->format->BytesPerPixel == 3){
        if(surface->format->Rmask == 0x000000ff)
        {
            mode = GL_RGB;
        }else{
            mode = GL_BGR;
        }
    }else{
        std::cout<<"Error: Cannot get mode for surface "<<std::endl;
        glDeleteTextures(1, &texture);
        return 0;
    }
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

bool inPolygon(std::vector<SDL_Point> points, int testX, int testY)
{
    int i;
    int j;
    bool ret = false;

    for (i = 0, j = points.size() - 1; i < points.size(); j = i++)
    {
        if(((points[i].y>testY) != (points[j].y>testY)) &&
            (testX < (points[j].x - points[i].x) *
            (testY - points[i].y) / (points[j].y - points[i].y) + points[i].x))
        {
            ret = !ret;
        }
    }
    return ret;
}

GLuint generateShapeTexture(Shape* shape)
{
    GLuint texture;
    SDL_Surface* surface;
    SDL_Color backgroundColor;

    backgroundColor.r = 0;
    backgroundColor.g = 0;
    backgroundColor.b = 0;
    backgroundColor.a = 255;

    if(shape->getNumPoints() < 3)
    {
        std::cerr<<"Error: Cannot create shape texture with less then 3 points"<<std::endl;
        return 0;
    }

    surface = SDL_CreateRGBSurface(0, shape->getRenderWidth(), shape->getRenderHeight(), 32, 0, 0, 0, 0);
    if(surface == NULL)
    {
        std::cerr<<"Error: Could not create surface "<<SDL_GetError()<<std::endl;
        return 0;
    }

    if(SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_ADD) != 0)
    {
        std::cerr<<"Error: Could not create surface "<<SDL_GetError()<<std::endl;
    }

    //Color surface
    for(unsigned int i = 0; i < surface->h; i++)
    {
        for(unsigned int j = 0; j < surface->w; j++)
        {
            if(inPolygon(shape->getPoints(), i, j))
            {
                setPixel(surface, (i * surface->w) + j, shape->getColor());
            }else{
                setPixel(surface, (i * surface->w) + j, backgroundColor);
            }
        }
    }

    texture = surfaceToTexture(surface);
    SDL_FreeSurface(surface);
    return texture;
}
