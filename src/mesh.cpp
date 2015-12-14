#include "mesh.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>


Mesh::Mesh(const std::string &fileName)
{
    InitMesh(ObjModel(fileName).ToIndexedModel());
}

void Mesh::InitMesh(const IndexedModel &model)
{
    _numIndices = model.indices.size();

    glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

}

Mesh::Mesh(Vertex *vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndices)
{
    IndexedModel model;

    for(unsigned int i = 0; i < numVertices; i++)
    {
        model.positions.push_back(*vertices[i].GetPos());
        model.texCoords.push_back(*vertices[i].GetTexCoord());
        model.normals.push_back(*vertices[i].GetNormal());
    }

    for(unsigned int i = 0; i < numIndices; i++)
    {
        model.indices.push_back(indices[i]);
    }

    InitMesh(model);
}

Mesh::~Mesh()
{
    glDeleteBuffers(NUM_BUFFERS, _vertexArrayBuffers);
    glDeleteVertexArrays(1, &_vertexArrayObject);
}

void Mesh::Draw()
{
    glBindVertexArray(_vertexArrayObject);
    glDrawElementsBaseVertex(GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0, 0);
    glBindVertexArray(0);
}
