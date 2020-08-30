#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include "navia/scene/Scene.hpp"
#include <entt/entt.hpp>

namespace Navia {
class Entity {
public:
    Entity() = default;
    Entity(entt::entity handle, Scene* scene);

    operator bool() const;
    operator uint32_t() const;

    friend bool operator==(const Entity& lhs, const Entity& rhs);
    friend bool operator!=(const Entity& lhs, const Entity& rhs);


    template <typename Component, typename ... Args>
    Component& addComponent(Args&& ... args) {
        NAVIA_CORE_ASSERT(!hasComponent<Component>(), "Entity already has given component!");
        return scene->registry.emplace<Component>(handle, std::forward<Args>(args)...);
    }

    template <typename Component>
    Component& getComponent() {
        NAVIA_CORE_ASSERT(hasComponent<Component>(), "Entity does not have given component!");
        return scene->registry.get<Component>(handle);
    }

    template <typename Component>
    bool hasComponent() {
        return scene->registry.has<Component>(handle);
    }

    template <typename Component>
    void removeComponent() {
        NAVIA_CORE_ASSERT(hasComponent<Component>(), "Entity does not have given component!");
        scene->registry.remove<Component>(handle);
    }

private:
    entt::entity handle = entt::null;
    Scene* scene = nullptr;
};
}

#endif