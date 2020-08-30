#ifndef _COMPONENTS_HPP_
#define _COMPONENTS_HPP_

#include <glm/glm.hpp>

namespace Navia {
struct TagComponent {
    std::string tag;

    TagComponent() = default;
    TagComponent(const std::string& tag);
};

struct TransformComponent {
    glm::mat4 transform{ 1.0f };

    TransformComponent() = default;
    TransformComponent(const glm::mat4& transform);

    TransformComponent& operator=(const TransformComponent& rhs) = default;

    operator glm::mat4&();
    operator const glm::mat4&() const;
};

struct SpriteComponent {
    glm::vec4 color{ 1.0f };

    SpriteComponent() = default;
    SpriteComponent(const glm::vec4& color);
};
}

#endif