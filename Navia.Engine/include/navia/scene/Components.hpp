#ifndef _COMPONENTS_HPP_
#define _COMPONENTS_HPP_

#include "navia/scene/SceneCamera.hpp"
#include "navia/scene/ScriptableEntity.hpp"
#include <glm/glm.hpp>

namespace Navia {
struct CameraComponent {
    SceneCamera camera;
    bool primary = true;
    bool fixedAspectRatio = false;
};

struct NativeScriptComponent {
    ScriptableEntity* entity = nullptr;

    ScriptableEntity*(*createScript)();
    void(*destroyScript)(NativeScriptComponent*);

    template <typename Script>
    void bind() {
        createScript = []() { return static_cast<ScriptableEntity*>(new Script()); };
        destroyScript = [](NativeScriptComponent* script) { delete script->entity; script->entity = nullptr; };
    }
};

struct TagComponent {
    std::string tag;

    TagComponent() = default;
    TagComponent(const std::string& tag);
};

struct TransformComponent {
    glm::vec3 translation{ 0.0f };
    glm::vec3 rotation{ 0.0f };
    glm::vec3 scale{ 1.0f };

    TransformComponent() = default;
    TransformComponent(const glm::vec3& translation);

    glm::mat4 getTransform() const;
};

struct SpriteComponent {
    glm::vec4 color{ 1.0f };

    SpriteComponent() = default;
    SpriteComponent(const glm::vec4& color);
};
}

#endif