#include "../include/Renderer.hpp"

#include "paintSurface.hpp"
#include "generateTexture.hpp"
#include "../utils/colorUtils.hpp"


Renderer::Renderer(int w, int h, unsigned int l)
{
    width = w;
    height = h;
    if(l > MAX_LAYERS || l < 1)
    {
        l = MAX_LAYERS;
    }
    numLayers = l;
    windowRect = {0, 0, (int)width, (int)height};
    useRenderCache = true;
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

GLuint Renderer::makeTexture(Renderable* renderable)
{
    Sprite* sprite;
    Colorable* colorable;
    Shape* shape;
    SDL_Surface* imageSurface;
    SDL_Surface* surface;
    GLuint texture;
    SDL_Rect bounds;
    Uint32 rMask;
    Uint32 gMask;
    Uint32 bMask;
    Uint32 aMask;
    std::unordered_map<std::string, GLuint>::const_iterator it;

    if(renderable == NULL)
    {
        return -1;
    }
    //If the texture already exists dont remake it
    if((it = textures.find(renderable->getId())) != textures.end())
    {
        return it->second;
    }
    //If we have  a shape generate, insert and return
    shape = dynamic_cast<Shape*>(renderable);
    if(shape != NULL)
    {
        texture = generateShapeTexture(shape);
        if(texture == 0)
        {
            return -1;
        }
        if(useRenderCache)
        {
            textures.insert(std::pair<std::string, GLuint>(shape->getId(), texture));
        }
        return texture;
    }

    //Check if we have a sprite
    sprite = dynamic_cast<Sprite*>(renderable);
    //If we don't have at least a sprite we cannot create a texture
    if(sprite == NULL)
    {
        return -1;
    }
    //Check if we have a colorable or a renderable
    colorable = dynamic_cast<Colorable*>(renderable);

    imageSurface = getSurface(sprite->getPath());
    if(imageSurface == NULL)
    {
        return -1;
    }

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rMask = 0xff000000;
        gMask = 0x00ff0000;
        bMask = 0x0000ff00;
        aMask = 0x000000ff;
    #else
        rMask = 0x000000ff;
        gMask = 0x0000ff00;
        bMask = 0x00ff0000;
        aMask = 0xff000000;
    #endif

    surface = SDL_CreateRGBSurface(0, sprite->getRenderWidth() * sprite->getScale(), sprite->getRenderHeight() * sprite->getScale(), 32, rMask, gMask, bMask, aMask);
    if(surface == NULL)
    {
        std::cerr<<"Error: Surface is NULL "<<SDL_GetError()<<std::endl;
        return -1;
    }

    if(SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE) < 0)
    {
        std::cerr<<"Error: Could not set surface blend mode "<<SDL_GetError()<<std::endl;
        SDL_FreeSurface(surface);
        return -1;
    }

    if(SDL_SetSurfaceBlendMode(imageSurface, SDL_BLENDMODE_NONE) < 0)
    {
        std::cerr<<"Error: Could not set surface blend mode "<<SDL_GetError()<<std::endl;
        SDL_FreeSurface(surface);
        return -1;
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
        return -1;
    }

    if(colorable)
    {
        (void)paintSurface(surface, *colorable, colorKeys[colorable->getPath()]);
    }

    texture = surfaceToTexture(surface);
    if(texture > 0 && useRenderCache)
    {
        textures.insert(std::pair<std::string, GLuint>(sprite->getId(), texture));
    }

    SDL_FreeSurface(surface);
    return texture;
}

bool Renderer::render(Renderable* renderable)
{
    Sprite* sprite;
    GLuint texture;
    GLuint maskTexture;
    SDL_Rect dest;

    if(renderable == NULL)
    {
        std::cerr<<"Error: Renderable is NULL"<<std::endl;
        return false;
    }

    if(renderable->getLayer() > numLayers)
    {
        std::cerr<<"Error: Renderable layer greater then max layer: "<<numLayers<<std::endl;
        return false;
    }

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

    texture = makeTexture(renderable);

    if(texture < 1)
    {
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, layerFrameBuffers[renderable->getLayer()]);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    glViewport(0, 0, width, height);

    if(basicShader.bind())
    {
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

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

bool Renderer::clear()
{
    for(int i = 0; i < numLayers; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, layerFrameBuffers[i]);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    return true;
}

void Renderer::update()
{

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    for(int i = 0; i < numLayers; i++)
    {
        if(basicShader.bind())
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, layerTextures[i]);

            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex2f(0, height);
                glTexCoord2f(1, 0); glVertex2f(width, height);
                glTexCoord2f(1, 1); glVertex2f(width, 0);
                glTexCoord2f(0, 1); glVertex2f(0, 0);
            glEnd();
            basicShader.unbind();
        }
    }

    SDL_GL_SwapWindow(window);
}

void Renderer::enableRenderCache()
{
    useRenderCache = true;
}

void Renderer::disableRenderCache()
{
    useRenderCache = false;
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
    //Cached object textures
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
    //Free render and frame buffers
    glDeleteTextures(numLayers, layerTextures);
    glDeleteFramebuffers(numLayers, layerFrameBuffers);
    delete[] layerTextures;
    delete[] layerFrameBuffers;
    SDL_DestroyWindow(window);
    maskShader.freeShader();
    basicShader.freeShader();
    window = NULL;
}
