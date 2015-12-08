#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
    Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
    {
        this->_pos = pos;
        this->_forward = glm::vec3(0.0f, 0.0f, 1.0f);
        this->_up = glm::vec3(0.0f, 1.0f, 0.0f);
        this->_projection = glm::perspective(fov, aspect, zNear, zFar);
    }

    inline glm::mat4 GetViewProjection() const
    {
        return _projection * glm::lookAt(_pos, _pos + _forward, _up);
    }

private:
    glm::mat4 _projection;
    glm::vec3 _pos;
    glm::vec3 _forward;
    glm::vec3 _up;

};
#endif // CAMERA_H
