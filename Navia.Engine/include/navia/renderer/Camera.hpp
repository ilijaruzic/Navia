#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <glm/glm.hpp>

namespace Navia {
class Camera {
public:
    Camera() = default;
    Camera(const glm::mat4& projection);
    virtual ~Camera() = default;

    const glm::mat4& getProjection() const;

protected:
    glm::mat4 projection{ 1.0f };
};
}

#endif