#include "navia/scene/SceneCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Navia {
SceneCamera::SceneCamera() {
    recalculateProjection();
}

SceneCamera::ProjectionType SceneCamera::getProjectionType() const {
    return projectionType;
}

void SceneCamera::setProjectionType(ProjectionType type) {
    projectionType = type;
    recalculateProjection();
}

float SceneCamera::getPerspectiveVerticalFOV() const {
    return perspectiveVerticalFOV;
}

void SceneCamera::setPerspectiveVerticalFOV(float fov) {
    perspectiveVerticalFOV = fov;
    recalculateProjection();
}

float SceneCamera::getPerspectiveNearClip() const {
    return perspectiveNearClip;
}

void SceneCamera::setPerspectiveNearClip(float nearClip) {
    perspectiveNearClip = nearClip;
    recalculateProjection();
}

float SceneCamera::getPerspectiveFarClip() const {
    return perspectiveFarClip;
}

void SceneCamera::setPerspectiveFarClip(float farClip) {
    perspectiveFarClip = farClip;
    recalculateProjection();
}

void SceneCamera::setPerspective(float fov, float nearClip, float farClip) {
    projectionType = ProjectionType::Perspective;
    perspectiveVerticalFOV = fov;
    perspectiveNearClip = nearClip;
    perspectiveFarClip = farClip;
    recalculateProjection();
}

float SceneCamera::getOrthographicSize() const {
    return orthographicSize;
}

void SceneCamera::setOrthographicSize(float size) {
    orthographicSize = size;
    recalculateProjection();
}

float SceneCamera::getOrthographicNearClip() const {
    return orthographicNearClip;
}

void SceneCamera::setOrthographicNearClip(float nearClip) {
    orthographicNearClip = nearClip;
    recalculateProjection();
}

float SceneCamera::getOrthographicFarClip() const {
    return orthographicFarClip;
}

void SceneCamera::setOrthographicFarClip(float farClip) {
    orthographicFarClip = farClip;
    recalculateProjection();
}

void SceneCamera::setOrthographic(float size, float nearClip, float farClip) {
    projectionType == ProjectionType::Orthographic;
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
    switch (projectionType) {
        case ProjectionType::Perspective:
        {
            projection = glm::perspective(perspectiveVerticalFOV, aspectRatio, perspectiveNearClip, perspectiveFarClip);
            break;
        }
        case ProjectionType::Orthographic:
        {
            float orthographicLeft = -orthographicSize * aspectRatio * 0.5f;
            float orthographicRight = orthographicSize * aspectRatio * 0.5f;
            float orthographicBottom = -orthographicSize * 0.5f;
            float orthographicTop = orthographicSize * 0.5f;
            projection = glm::ortho(orthographicLeft, orthographicRight, orthographicBottom, orthographicTop, orthographicNearClip, orthographicFarClip);
            break;
        }
    }
}
}