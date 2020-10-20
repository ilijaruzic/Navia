#include "navia/scene/Components.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Navia {
TagComponent::TagComponent(const std::string& tag) : tag(tag) {}

TransformComponent::TransformComponent(const glm::vec3& translation) : translation(translation) {}

glm::mat4 TransformComponent::getTransform() const {
    glm::mat4 rotation = glm::rotate(glm::mat4{ 1.0f }, this->rotation.x, glm::vec3{ 1.0f, 0.0f, 0.0f }) *
            glm::rotate(glm::mat4{ 1.0f }, this->rotation.y, glm::vec3{ 0.0f, 1.0f, 0.0f }) *
            glm::rotate(glm::mat4{ 1.0f }, this->rotation.z, glm::vec3{ 0.0f, 0.0f, 1.0f });

    return glm::translate(glm::mat4{ 1.0f }, translation) * rotation * glm::scale(glm::mat4{ 1.0f }, scale);
}

SpriteComponent::SpriteComponent(const glm::vec4& color) : color(color) {}
}