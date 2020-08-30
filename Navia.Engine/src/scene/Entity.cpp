#include "navia/scene/Entity.hpp"

namespace Navia {
Entity::Entity(entt::entity handle, Navia::Scene* scene) : handle(handle), scene(scene) {}

Entity::operator bool() const {
    return handle != entt::null;
}

Entity::operator uint32_t() const {
    return static_cast<uint32_t>(handle);
}

bool operator==(const Entity& lhs, const Entity& rhs) {
    return lhs.handle == rhs.handle && lhs.scene == rhs.scene;
}

bool operator!=(const Entity& lhs, const Entity& rhs) {
    return !(lhs == rhs);
}
}