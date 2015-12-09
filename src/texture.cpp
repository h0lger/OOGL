#include "texture.h"
#include <SOIL/SOIL.h>
#include <iostream>

Texture::Texture(const std::string &fileName)
{
    int x, y, numComponents;
    unsigned char* data = SOIL_load_image((fileName).c_str(), &x, &y, &numComponents, SOIL_LOAD_RGBA);
    if(data == NULL)
        std::cerr << "Error loading texture: " << fileName << std::endl;

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    SOIL_free_image_data(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_texture);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, _texture);
}
