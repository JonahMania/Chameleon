#include "../../include/Shader.hpp"

Shader::Shader()
{
    id = 0;
}

bool Shader::load()
{
    return false;
}

bool Shader::bind()
{
    GLenum error;

    glUseProgram(id);

    error = glGetError();
    if(error != GL_NO_ERROR)
    {
        std::cerr<<"Error: Could not bind shader "<<gluErrorString(error)<<std::endl;
        printShaderProgramLog(id);
        return false;
    }
    return true;
}

bool Shader::unbind()
{
    glUseProgram(0);
}

GLuint Shader::getId()
{
    return id;
}

void Shader::freeShader()
{
    glDeleteProgram(id);
}

Shader::~Shader()
{
    freeShader();
}

void Shader::printShaderProgramLog(GLuint program)
{
    GLint maxLength = 0;

    if(!glIsProgram(program))
    {
        std::cout<<"Error: "<<program<<" is not a shader program"<<std::endl;
        return;
    }

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    if(maxLength < 1)
    {
        return;
    }
    GLchar* infoLog = new GLchar[maxLength];
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    std::cerr<<infoLog<<std::endl;
    delete[] infoLog;
}

void Shader::printShaderLog(GLuint shader)
{
    GLint maxLength = 0;

    if(!glIsShader(shader))
    {
        std::cout<<"Error: "<<shader<<" is not a shader"<<std::endl;
        return;
    }

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    if(maxLength < 1)
    {
        return;
    }
    GLchar* infoLog = new GLchar[maxLength];
    glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

    std::cerr<<infoLog<<std::endl;
    delete[] infoLog;
}
