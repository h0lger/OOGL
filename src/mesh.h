#ifndef MESH_H
#define MESH_H
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "objLoader.h"

struct Vertex
{
public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
    {
        this->_pos = pos;
        this->_texCoord = texCoord;
        this->_normal = normal;
    }

    glm::vec3* GetPos() { return &_pos; }
    glm::vec2* GetTexCoord() { return &_texCoord; }
    glm::vec3* GetNormal() { return &_normal; }

private:
    glm::vec3 _pos;
    glm::vec2 _texCoord;
    glm::vec3 _normal;

};

enum MeshBufferPositions
{
    POSITION_VB,
    TEXCOORD_VB,
    NORMAL_VB,
    INDEX_VB
};

class Mesh
{
public:
    Mesh(const std::string& fileName);
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

    void Draw();

    virtual ~Mesh();

private:
    static const unsigned int NUM_BUFFERS = 4;
    void operator=(const Mesh& mesh) {}
    Mesh(const Mesh& mesh) {}

    void InitMesh(const IndexedModel& model);

    GLuint _vertexArrayObject;
    GLuint _vertexArrayBuffers[NUM_BUFFERS];
    unsigned int _numIndices;
};


#endif // MESH_H
