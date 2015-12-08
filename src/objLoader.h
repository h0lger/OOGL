#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <glm/glm.hpp>
#include <vector>
#include <string>

struct ObjIndex
{
    unsigned int vertexIndex;
    unsigned int uvIndex;
    unsigned int normalIndex;

    bool operator<(const ObjIndex& r) const
    {
        return vertexIndex < r.vertexIndex;
    }
};

class IndexedModel
{
public:
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    void CalcNormals();
};

class ObjModel
{
public:
    std::vector<ObjIndex> ObjIndices;
    std::vector<glm::vec3> Vertices;
    std::vector<glm::vec3> UVs;
    std::vector<glm::vec3> Normals;
    bool HasUVs;
    bool HasNormals;

    ObjModel(const std::string& fileName);
    IndexedModel ToIndexModel();

private:
    unsigned int FindLastVertexIndex(const std::vector<ObjIndex*>& indexLookup, const ObjIndex* currentIndex, const IndexedModel& result);
    void CreateObjFace(const std::string& line);

    glm::vec2 ParseObjVec2(const std::string& line);
    glm::vec3 ParseObjVec3(const std::string& line);
    ObjIndex ParseObjIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};

#endif // OBJLOADER_H
