#include "paintSurface.hpp"
#include "generateTexture.hpp"
#include "../utils/colorUtils.hpp"
#include "../include/Renderer.hpp"

Renderer::Renderer(int w, int h)
{
    width = w;
    height = h;
    windowRect = {0, 0, width, height};
}

SDL_Surface* Renderer::getSurface(std::string path)
{
    std::unordered_map<std::string, SDL_Surface*>::const_iterator it;
    SDL_Surface* surface;

    //Check if we have the surface in cache
    it = surfaces.find(path);
    if(it != surfaces.end())
    {
        return it->second;
    }
    //If the surface does not exist create it
    surface = IMG_Load(path.c_str());
    if(surface == NULL)
    {
        std::cerr<<"Error: Could not load surface at path '"<<path<<"' "<<IMG_GetError()<<std::endl;
        return NULL;
    }

    //Get color keys from surface and insert them into the map
    colorKeys.insert(std::pair<std::string, std::set<SDL_Color>>(path, getColorKeys(surface)));
    //Add new surface to cache
    surfaces.insert(std::pair<std::string, SDL_Surface*>(path, surface));
    return surface;
}

bool Renderer::makeTexture(Renderable* renderable)
{
    Sprite* sprite;
    Colorable* colorable;
    Shape* shape;
    SDL_Surface* imageSurface;
    SDL_Surface* surface;
    GLuint texture;
    SDL_Rect bounds;

    if(renderable == NULL)
    {
        return false;
    }
    //If the texture already exists dont remake it
    if(textures.find(renderable->getId()) != textures.end())
    {
        return true;
    }
    //If we have  a shape generate, insert and return
    shape = dynamic_cast<Shape*>(renderable);
    if(shape != NULL)
    {
        texture = generateShapeTexture(shape);
        if(texture == 0)
        {
            return false;
        }
        textures.insert(std::pair<std::string, GLuint>(shape->getId(), texture));
        return true;
    }

    //Check if we have a sprite
    sprite = dynamic_cast<Sprite*>(renderable);
    //If we don't have at least a sprite we cannot create a texture
    if(sprite == NULL)
    {
        return false;
    }
    //Check if we have a colorable or a renderable
    colorable = dynamic_cast<Colorable*>(renderable);

    imageSurface = getSurface(sprite->getPath());
    if(imageSurface == NULL)
    {
        return false;
    }

    surface = SDL_CreateRGBSurface(0, sprite->getRenderWidth() * sprite->getScale(), sprite->getRenderHeight() * sprite->getScale(), 32, 0, 0, 0, 0);
    if(surface == NULL)
    {
        std::cerr<<"Error: Surface is NULL "<<SDL_GetError()<<std::endl;
        return false;
    }

    //Find the position of sprite sheet we want to use
    bounds.w = sprite->getRenderWidth();
    bounds.h = sprite->getRenderHeight();
    bounds.x = sprite->getSheetPositionX();
    bounds.y = sprite->getSheetPositionY();

    if(SDL_BlitScaled(imageSurface, &bounds, surface, NULL) < 0)
    {
        std::cerr<<"Error: Could not blit surface "<<SDL_GetError()<<std::endl;
        SDL_FreeSurface(surface);
        return false;
    }

    if(colorable)
    {
        (void)paintSurface(surface, *colorable, colorKeys[colorable->getPath()]);
    }

    texture = surfaceToTexture(surface);
    if(texture > 0)
    {
        textures.insert(std::pair<std::string, GLuint>(sprite->getId(), texture));
    }

    SDL_FreeSurface(surface);
    return true;
}

bool Renderer::render(Renderable* renderable, Renderable* mask)
{
    Sprite* sprite;
    GLuint texture;
    GLuint maskTexture;
    SDL_Rect dest;
    std::unordered_map<std::string, GLuint>::const_iterator it;

    sprite = dynamic_cast<Sprite*>(renderable);

    dest.x = renderable->getRenderPositionX();
    dest.y = renderable->getRenderPositionY();
    dest.w = renderable->getRenderWidth();
    dest.h = renderable->getRenderHeight();
    //If we have a sprite multiply by scale
    if(sprite != NULL)
    {
        dest.w *= sprite->getScale();
        dest.h *= sprite->getScale();
    }
    //Check if this texture is on the screen if not don't render it
    if((dest.x + dest.w) < 0 || dest.x > width
    && (dest.y + dest.h) < 0 || dest.y > height)
    {
        return false;
    }

    (void)makeTexture(renderable);

    it = textures.find(renderable->getId());
    if(it == textures.end())
    {
        return false;
    }
    texture = it->second;

    if(texture < 1)
    {
        return false;
    }

    if(mask != NULL && maskShader.bind())
    {
        (void)makeTexture(mask);

        it = textures.find(mask->getId());
        if(it == textures.end())
        {
            return false;
        }
        maskTexture = it->second;

        if(maskTexture < 1)
        {
            return false;
        }
        //Render wih mask
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, maskTexture);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(dest.x, dest.y);
            glTexCoord2f(1, 0); glVertex2f(dest.x + dest.w, dest.y);
            glTexCoord2f(1, 1); glVertex2f(dest.x + dest.w, dest.y + dest.h);
            glTexCoord2f(0, 1); glVertex2f(dest.x, dest.y + dest.h);
        glEnd();

        maskShader.unbind();
    }else if(basicShader.bind()){
        //Render without mask
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(dest.x, dest.y);
            glTexCoord2f(1, 0); glVertex2f(dest.x + dest.w, dest.y);
            glTexCoord2f(1, 1); glVertex2f(dest.x + dest.w, dest.y + dest.h);
            glTexCoord2f(0, 1); glVertex2f(dest.x, dest.y + dest.h);
        glEnd();

        basicShader.unbind();
    }

}

bool Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
    return true;
}

void Renderer::update()
{
    SDL_GL_SwapWindow(window);
}

bool Renderer::freeAllSurfaces()
{
    for(auto &surface : surfaces)
    {
        if(surface.second)
        {
            std::cout<<"FREEING SURFACE "<<surface.first<<std::endl;
            SDL_FreeSurface(surface.second);
        }
    }
    surfaces.clear();
}

bool Renderer::freeAllTextures()
{
    for(auto &texture : textures)
    {
        if(texture.second != 0)
        {
            std::cout<<"FREEING TEXTURE "<<texture.first<<std::endl;
            glDeleteTextures(1, &texture.second);
        }
    }
    textures.clear();
}

bool Renderer::freeAll()
{
    return freeAllTextures() && freeAllSurfaces();
}

Renderer::~Renderer()
{
    std::cout<<"FREEING RENDERER"<<std::endl;
    freeAll();
    SDL_DestroyWindow(window);
    maskShader.freeShader();
    basicShader.freeShader();
    window = NULL;
}
