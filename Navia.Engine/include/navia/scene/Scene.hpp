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

    Entity createEntity(const std::string& name = std::string{});

private:
    entt::registry registry;

    friend class Entity;
};
}

#endif