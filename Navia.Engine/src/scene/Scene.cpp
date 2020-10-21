#include "navia/renderer/Renderer2D.hpp"
#include "navia/scene/Components.hpp"
#include "navia/scene/Scene.hpp"
#include <glm/glm.hpp>

namespace Navia {
Scene::Scene() {}

Scene::~Scene() {}

void Scene::onUpdate(Timestep timestep) {
    {
        registry.view<NativeScriptComponent>().each([=](auto handle, auto& script) {
            if (!script.entity) {
                script.entity = script.createScript();
                script.entity->entity = Entity{ handle, this };
                script.entity->onCreate();
            }
            script.entity->onUpdate(timestep);
        });
    }

    Camera* mainCamera = nullptr;
    glm::mat4 mainCameraTransform;
    {
        auto view = registry.view<TransformComponent, CameraComponent>();
        for (auto entity : view) {
            auto[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
            if (camera.primary) {
                mainCamera = &camera.camera;
                mainCameraTransform = transform.getTransform();
                break;
            }
        }
    }

    if (mainCamera) {
        Renderer2D::beginScene(mainCamera->getProjection(), mainCameraTransform);

        auto group = registry.group<TransformComponent>(entt::get<SpriteComponent>);
        for (auto entity : group) {
            auto[transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
            Renderer2D::drawQuad(transform.getTransform(), sprite.color);
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
    tag.tag = name.empty() ? "Untitled Entity" : name;
    entity.addComponent<TransformComponent>();
    return entity;
}

void Scene::destroyEntity(Entity entity) {
    registry.destroy(entity);
}

template <typename Component>
void Scene::onComponentAdded(Entity entity, Component& component) {
    static_assert(false);
}

template <>
void Scene::onComponentAdded<CameraComponent>(Entity entity, CameraComponent& component) {
    component.camera.setViewportSize(viewportWidth, viewportHeight);
}

template <>
void Scene::onComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component) {}

template <>
void Scene::onComponentAdded<TagComponent>(Entity entity, TagComponent& component) {}

template <>
void Scene::onComponentAdded<TransformComponent>(Entity entity, TransformComponent& component) {}

template <>
void Scene::onComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& component) {}
}