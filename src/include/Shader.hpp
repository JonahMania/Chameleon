#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#define GL_GLEXT_PROTOTYPES

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

class Shader
{
    public:
        Shader();
        virtual bool load();
        //Binds this shader
        bool bind();
        //Binds the default shader
        bool unbind();
        //Returns the OpenGL shader id
        GLuint getId();
        virtual void freeShader();
        virtual ~Shader();
    protected:
        void printShaderProgramLog(GLuint program);
        void printShaderLog(GLuint shader);
        GLuint id;
};

#endif
