#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include "navia/core/Base.hpp"
#include "navia/core/Timestep.hpp"
#include <entt/entt.hpp>

namespace Navia {
class Entity;

class Scene {
public:
    Scene();
    ~Scene();

    void onUpdate(Timestep timestep);
    void onViewportResize(uint32_t width, uint32_t height);

    Entity createEntity(const std::string& name = std::string{});

private:
    entt::registry registry;
    uint32_t viewportWidth = 0;
    uint32_t viewportHeight = 0;

    friend class Entity;
    friend class SceneHierarchyPanel;
};
}

#endif