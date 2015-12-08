#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include<GL/gl.h>

class Texture
{
public:
    Texture(const std::string& fileName);
    void Bind();
    virtual ~Texture();

private:
    Texture(const Texture& texture) {}
    void operator=(const Texture& texture) {}

    GLuint _m_texture;
};

#endif // TEXTURE_H
