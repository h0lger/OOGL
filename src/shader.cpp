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
    CheckForErrors(_program, GL_LINK_STATUS, true, "Error linking shader program");

    glValidateProgram(_program);
    CheckForErrors(_program, GL_LINK_STATUS, true, "Invalid shader program");

    _uniforms[0] = glGetUniformLocation(_program, "MVP");
    _uniforms[1] = glGetUniformLocation(_program, "Normal");
    _uniforms[2] = glGetUniformLocation(_program, "lightDirection");
}

Shader::~Shader()
{
    for(unsigned int i = 0; i< NUM_SHADERS; i++)
    {
        glDetachShader(_program, _shaders[i]);
        glDeleteShader(_shaders[i]);
    }

    glDeleteProgram(_program);
}

void Shader::Update(const Transform &transform, const Camera &camera)
{
    glm::mat4 MVP = transform.GetMVP(camera);
    glm::mat4 Normal = transform.GetModel();

    glUniformMatrix4fv(_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(_uniforms[1], 1, GL_FALSE, &Normal[0][0]);
    glUniform3f(_uniforms[2], 0.0f, 0.0f, 1.0f);
}

std::string Shader::LoadShader(const std::string &fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Error loading shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::CheckForErrors(GLuint shader, GLuint flag, bool isProgram, const std::string &errMsg)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errMsg << ": '" << error << "'" << std::endl;
    }
}

GLuint Shader::CreateShader(const std::string &text, unsigned int type)
{
    GLuint shader = glCreateShader(type);

    if(shader == 0)
        std::cerr << "Error compiling shader type " << type << std::endl;

    const GLchar* p[1];
    p[0] = text.c_str();
    GLint lenghts[1];
    lenghts[0] = text.length();

    glShaderSource(shader, 1, p, lenghts);
    glCompileShader(shader);

    CheckForErrors(shader, GL_COMPILE_STATUS, false, "Error compiling shader");

    return shader;
}
