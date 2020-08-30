#include "navia/scene/Components.hpp"

namespace Navia {
TagComponent::TagComponent(const std::string& tag) : tag(tag) {}

TransformComponent::TransformComponent(const glm::mat4& transform) : transform(transform) {}

TransformComponent::operator glm::mat4&() {
    return transform;
}

TransformComponent::operator const glm::mat4&() const {
    return transform;
}

SpriteComponent::SpriteComponent(const glm::vec4& color) : color(color) {}
}