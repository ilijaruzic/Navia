#include "navia/scene/SceneCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Navia {
SceneCamera::SceneCamera() {
    recalculateProjection();
}

float SceneCamera::getOrthographicSize() const {
    return orthographicSize;
}

void SceneCamera::setOrthographicSize(float size) {
    orthographicSize = size;
    recalculateProjection();
}

void SceneCamera::setOrthographic(float size, float nearClip, float farClip) {
    orthographicSize = size;
    orthographicNearClip = nearClip;
    orthographicFarClip = farClip;
    recalculateProjection();
}

void SceneCamera::setViewportSize(uint32_t width, uint32_t height) {
    aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    recalculateProjection();
}

void SceneCamera::recalculateProjection() {
    float orthographicLeft = -orthographicSize * aspectRatio * 0.5f;
    float orthographicRight = orthographicSize * aspectRatio * 0.5f;
    float orthographicBottom = -orthographicSize * 0.5f;
    float orthographicTop = orthographicSize * 0.5f;
    projection = glm::ortho(orthographicLeft, orthographicRight, orthographicBottom, orthographicTop, orthographicNearClip, orthographicFarClip);
}
}