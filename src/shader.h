#ifndef SHADER_INC_H
#define SHADER_INC_H
#include <string>
#include <GL/gl.h>
#include "transform.h"

class Shader
{
public:
    Shader(const std::string& fileName);

    void Bind();
    void Update(const Transform& transform, const Camera& camera);

    virtual ~Shader();

private:
    static const unsigned int NUM_SHADERS = 2;
    static const unsigned int NUM_UNIFORMS = 3;
    void operator=(const Shader& shader) {}
    Shader(const Shader& shader);

    std::string LoadShader(const std::string& fileName);
    void CheckForErrors(GLuint shader, GLuint flag, bool isProgram, const std::string& errMsg);
    GLuint CreateShader(const std::string& text, unsigned int type);

    GLuint _program;
    GLuint _shaders[NUM_SHADERS];
    GLuint _uniforms[NUM_UNIFORMS];

};


#endif // SHADER_INC_H
