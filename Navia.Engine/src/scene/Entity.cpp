#include "navia/scene/Entity.hpp"

namespace Navia {
Entity::Entity(entt::entity handle, Navia::Scene* scene) : handle(handle), scene(scene) {}

Entity::operator bool() const {
    return handle != entt::null;
}
}