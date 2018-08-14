#include "../include/Renderer.hpp"

bool Renderer::initialize()
{
    //Initialize SDL library
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr<<"ERROR: SDL could not initialize "<<SDL_GetError()<<std::endl;
        return false;
    }

    //Create window
    window = SDL_CreateWindow("Chameleon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        std::cerr<<"ERROR: Window was not created "<<SDL_GetError()<<std::endl;
        return false;
    }

    context = SDL_GL_CreateContext(window);
    if(context == NULL)
    {
        std::cerr<<"ERROR: OpenGL context was not created "<<SDL_GetError()<<std::endl;
        return false;
    }

    //Set OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    //Set double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Set otho projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //Enable 2d textures
    glEnable(GL_TEXTURE_2D);

    glClearColor(0, 0, 0, 0);

    //Enable blending
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Use Vsync
    if(SDL_GL_SetSwapInterval(1) < 0)
    {
        std::cout<<"WARNING: Could not set vsync "<<SDL_GetError()<<std::endl;
    }

    //Initilize PNG loading
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr<<"ERROR: PNG loading was not initilized "<<IMG_GetError()<<std::endl;
        return false;
    }

    if(!basicShader.load())
    {
        return false;
    }

    if(!maskShader.load())
    {
        return false;
    }

    //Allocate space for render and frame buffers
    layerTextures = new GLuint[numLayers];
    layerFrameBuffers = new GLuint[numLayers];
    //Create opengl frame and render buffer objects
    glGenTextures(numLayers, layerTextures);
    glGenFramebuffers(numLayers, layerFrameBuffers);

    for(int i = 0; i < numLayers; i++)
    {
        glBindTexture(GL_TEXTURE_2D, layerTextures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindFramebuffer(GL_FRAMEBUFFER, layerFrameBuffers[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, layerTextures[i], 0);
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

        if(status != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout<<"Error: Could not create framebuffer "<<glGetError()<<std::endl;
            glDeleteTextures(numLayers, layerTextures);
            glDeleteFramebuffers(numLayers, layerFrameBuffers);
            delete[] layerTextures;
            delete[] layerFrameBuffers;
            return false;
        }

    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}
