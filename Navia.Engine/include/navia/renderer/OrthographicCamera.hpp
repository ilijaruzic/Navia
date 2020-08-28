#ifndef _ORTHOGRAPHIC_CAMERA_HPP_
#define _ORTHOGRAPHIC_CAMERA_HPP_

#include <glm/glm.hpp>

namespace Navia {
class OrthographicCamera {
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    void setProjection(float left, float right, float bottom, float top);

    const glm::vec3& getPosition() const;
    float getRotation() const;
    const glm::mat4& getViewMatrix() const;
    const glm::mat4& getProjectionMatrix() const;
    const glm::mat4& getViewProjectionMatrix() const;

    void setPosition(const glm::vec3& position);
    void setRotation(float rotation);

public:
    glm::vec3 position{ 0.0f };
    float rotation{ 0.0f };

    glm::mat4 viewMatrix{ 1.0f };
    glm::mat4 projectionMatrix;
    glm::mat4 viewProjectionMatrix;

    void recalculateViewMatrix();
};
}

#endif