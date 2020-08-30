#include "navia/renderer/Renderer2D.hpp"
#include "navia/scene/Components.hpp"
#include "navia/scene/Entity.hpp"
#include "navia/scene/Scene.hpp"
#include <glm/glm.hpp>

namespace Navia {
Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::onUpdate(Timestep timestep) {
    auto group = registry.group<TransformComponent>(entt::get<SpriteComponent>);
    for (auto entity : group) {
        const auto&[transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
        Renderer2D::drawQuad(transform, sprite.color);
    }
}

Entity Scene::createEntity(const std::string& name) {
    Entity entity{ registry.create(), this };
    auto& tag = entity.addComponent<TagComponent>(name);
    tag.tag = name.empty() ? "Entity" : name;
    entity.addComponent<TransformComponent>();
    return entity;
}
}