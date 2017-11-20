#ifndef _STANDARDSHADER_HPP_
#define _STANDARDSHADER_HPP_

#include "Shader.hpp"

class BasicShader : public Shader
{
    public:
        bool load();
        bool bind();
    private:
};

#endif
