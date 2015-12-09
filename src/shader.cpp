#include "shader.h"
#include <iostream>
#include <fstream>


Shader::Shader(const std::string &fileName)
{
    _program = glCreateProgram();
    _shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    _shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    for(unsigned int i = 0;i < NUM_SHADERS; i++)
        glAttachShader(_program, _shaders[i]);

    glBindAttribLocation(_program, 0, "position");
    glBindAttribLocation(_program, 1, "texCoord");
    glBindAttribLocation(_program, 2, "normal");

    glLinkProgram(_program);
}
