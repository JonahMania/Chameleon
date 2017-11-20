#include "../../include/MaskShader.hpp"

bool MaskShader::load()
{
   GLint success = GL_TRUE;
   GLuint vertexShader;
   GLuint fragmentShader;
   GLint compiled;

   //Vertex shader program
   const GLchar* vertexShaderSource[] =
   {
       "varying vec2 vTexCoord;"
       "void main(void){"
           "vTexCoord = gl_MultiTexCoord0;"
           "gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
       "}"
   };

   //Fragment shader program
   const GLchar* fragmentShaderSource[] =
   {
        "uniform sampler2D texture;"
        "uniform sampler2D mask;"
        "varying vec2 vTexCoord;"
        "void main() {"
            "vec4 color = texture2D(texture, vTexCoord);"
            "vec4 maskColor  = texture2D(mask, vTexCoord);"
            "gl_FragColor = color.rgba * (1.0 - maskColor.a);"
        "}"
   };

   id = glCreateProgram();

   //Vertex shader
   vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
   glCompileShader(vertexShader);

   compiled = GL_FALSE;
   glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
   if(compiled != GL_TRUE)
   {
       std::cerr<<"Error: Could not compile vertex shader "<<vertexShader<<std::endl;
       printShaderLog(vertexShader);
       return false;
   }

   glAttachShader(id, vertexShader);

   //Fragment shader
   fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
   glCompileShader(fragmentShader);

   compiled = GL_FALSE;
   glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
   if(compiled != GL_TRUE)
   {
       std::cerr<<"Error: Could not compile fragment shader "<<vertexShader<<std::endl;
       printShaderLog(fragmentShader);
       return false;
   }

   glAttachShader(id, fragmentShader);

   //Link
   glLinkProgram(id);

   glGetProgramiv(id, GL_LINK_STATUS, &success);
   if(success != GL_TRUE)
   {
       std::cerr<<"Error: Could not link program "<<id<<std::endl;
       printShaderProgramLog(id);
       return false;
   }

   return true;
}

bool MaskShader::bind()
{
    if(Shader::bind())
    {
        GLuint t1Location = glGetUniformLocation(id, "texture");
        GLuint t2Location = glGetUniformLocation(id, "mask");

        glUniform1i(t1Location, 0);
        glUniform1i(t2Location, 1);
        return true;
    }
    return false;
}
