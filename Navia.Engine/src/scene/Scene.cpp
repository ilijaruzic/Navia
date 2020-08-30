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
    Camera* mainCamera = nullptr;
    glm::mat4* mainCameraTransform = nullptr;
    {
        auto view = registry.view<TransformComponent, CameraComponent>();
        for (auto entity : view) {
            auto[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
            if (camera.primary) {
                mainCamera = &camera.camera;
                mainCameraTransform = &transform.transform;
                break;
            }
        }
    }

    if (mainCamera) {
        Renderer2D::beginScene(mainCamera->getProjection(), *mainCameraTransform);

        auto group = registry.group<TransformComponent>(entt::get<SpriteComponent>);
        for (auto entity : group) {
            auto[transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
            Renderer2D::drawQuad(transform, sprite.color);
        }

        Renderer2D::endScene();
    }
}


void Scene::onViewportResize(uint32_t width, uint32_t height) {
    viewportWidth = width;
    viewportHeight = height;

    auto view = registry.view<CameraComponent>();
    for (auto entity : view) {
        auto& camera = view.get<CameraComponent>(entity);
        if (!camera.fixedAspectRatio) {
            camera.camera.setViewportSize(width, height);
        }
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