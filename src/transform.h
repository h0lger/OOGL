#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "camera.h"

struct Transform
{
public:
    Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
    {
        this->_pos = pos;
        this->_rot = rot;
        this->_scale = scale;
    }

    inline glm::mat4 GetModel() const
    {
        glm::mat4 posMat = glm::translate(_pos);
        glm::mat4 scaleMat = glm::scale(_scale);
        glm::mat4 rotX = glm::rotate(_rot.x, glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 rotY = glm::rotate(_rot.y, glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 rotZ = glm::rotate(_rot.z, glm::vec3(0.0, 0.0, 1.0));
        glm::mat4 rotMat = rotX * rotY * rotZ;


        return posMat * rotMat * scaleMat;
    }

    inline glm::mat4 GetMVP(const Camera& camera) const
    {
        glm::mat4 VP = camera.GetViewProjection();
        glm::mat4 M = GetModel();

        return VP * M;
    }

    inline glm::vec3* GetPos() { return &_pos; }
    inline glm::vec3* GetRot() { return &_rot; }
    inline glm::vec3* GetScale() { return &_scale; }

    inline void SetPos(glm::vec3& pos) { this->_pos = pos; }
    inline void SetRot(glm::vec3& rot) { this->_rot = rot; }
    inline void SetScale(glm::vec3& scale) { this->_scale = scale; }

private:
    glm::vec3 _pos;
    glm::vec3 _rot;
    glm::vec3 _scale;
};

#endif // TRANSFORM_H
