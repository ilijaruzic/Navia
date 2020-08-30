#include "navia/renderer/Camera.hpp"

namespace Navia {
Camera::Camera(const glm::mat4& projection) : projection(projection) {}

const glm::mat4& Camera::getProjection() const {
    return projection;
}
}