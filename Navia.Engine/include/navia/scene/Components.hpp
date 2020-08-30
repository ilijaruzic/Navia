#ifndef _COMPONENTS_HPP_
#define _COMPONENTS_HPP_

#include "navia/scene/SceneCamera.hpp"
#include <glm/glm.hpp>

namespace Navia {
struct CameraComponent {
    SceneCamera camera;
    bool primary = true;
    bool fixedAspectRatio = false;
};

struct TagComponent {
    std::string tag;

    TagComponent() = default;
    TagComponent(const std::string& tag);
};

struct TransformComponent {
    glm::mat4 transform{ 1.0f };

    TransformComponent() = default;
    TransformComponent(const glm::mat4& transform);

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