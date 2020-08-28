#include "navia/renderer/OrthographicCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Navia {
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), viewProjectionMatrix(projectionMatrix * viewMatrix) {
    NAVIA_PROFILE_FUNCTION();
}

void OrthographicCamera::setProjection(float left, float right, float bottom, float top) {
    NAVIA_PROFILE_FUNCTION();

    projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    viewProjectionMatrix = projectionMatrix * viewMatrix;
}

const glm::vec3& OrthographicCamera::getPosition() const {
    return position;
}

float OrthographicCamera::getRotation() const {
    return rotation;
}

const glm::mat4& OrthographicCamera::getViewMatrix() const {
    return viewMatrix;
}

const glm::mat4& OrthographicCamera::getProjectionMatrix() const {
    return projectionMatrix;
}

const glm::mat4& OrthographicCamera::getViewProjectionMatrix() const {
    return viewProjectionMatrix;
}

void OrthographicCamera::setPosition(const glm::vec3& position) {
    this->position = position;
    recalculateViewMatrix();
}

void OrthographicCamera::setRotation(float rotation) {
    this->rotation = rotation;
    recalculateViewMatrix();
}

void OrthographicCamera::recalculateViewMatrix() {
    NAVIA_PROFILE_FUNCTION();

    glm::mat4 transform =
            glm::translate(glm::mat4{ 1.0f }, position) *
            glm::rotate(glm::mat4{ 1.0f}, glm::radians(rotation), glm::vec3{ 0.0f, 0.0f, 1.0f });

    viewMatrix = glm::inverse(transform);
    viewProjectionMatrix = projectionMatrix * viewMatrix;
}
}