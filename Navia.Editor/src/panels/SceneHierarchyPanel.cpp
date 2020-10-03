#include "panels/SceneHierarchyPanel.hpp"
#include "navia/scene/Components.hpp"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Navia {
SceneHierarchyPanel::SceneHierarchyPanel(Ref<Scene> scene) {
    setContext(scene);
}

void SceneHierarchyPanel::setContext(Ref<Scene> scene) {
    this->scene = scene;
}

void SceneHierarchyPanel::onImGuiRender() {
    ImGui::Begin("Scene Hierarchy");
    scene->registry.each([&](auto handle) {
        Entity entity{ handle, scene.get() };
        drawEntityNode(entity);
    });
    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered()) {
        selectedEntity = Entity{};
    }
    ImGui::End();

    ImGui::Begin("Properties");
    if (selectedEntity) {
        drawEntityComponents(selectedEntity);
    }
    ImGui::End();
}

void SceneHierarchyPanel::drawEntityNode(Entity entity) {
    auto& tag = entity.getComponent<TagComponent>().tag;
    ImGuiTreeNodeFlags flags = (selectedEntity == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>(static_cast<uint64_t>(static_cast<uint32_t>(entity))), flags, "%s", tag.c_str());
    if (ImGui::IsItemClicked()) {
        selectedEntity = entity;
    }
    if (opened) {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>(9817239), flags, "%s", tag.c_str());
        if (opened) {
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
}

void SceneHierarchyPanel::drawEntityComponents(Entity entity) {
    entity.drawComponent<TagComponent>("Tag", [&]() {
        auto& tag = entity.getComponent<TagComponent>().tag;
        char buffer[256];
        std::memset(buffer, 0, sizeof(buffer));
        std::memcpy(buffer, tag.c_str(), sizeof(buffer));
        if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
            tag = std::string{ buffer };
        }
    });
    entity.drawComponent<TransformComponent>("Transform", [&]() {
        auto& transform = entity.getComponent<TransformComponent>().transform;
        ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
    });
    entity.drawComponent<CameraComponent>("Camera", [&]() {
        auto& component = entity.getComponent<CameraComponent>();
        auto& camera = component.camera;
        ImGui::Checkbox("Primary", &component.primary);
        const char* projectionTypes[] = { "Perspective", "Orthographic" };
        const char* currentProjectionType = projectionTypes[static_cast<int>(camera.getProjectionType())];
        if (ImGui::BeginCombo("Projection", currentProjectionType)) {
            for (int i = 0; i < 2; ++i) {
                bool selected = currentProjectionType == projectionTypes[i];
                if (ImGui::Selectable(projectionTypes[i], selected)) {
                    currentProjectionType = projectionTypes[i];
                    camera.setProjectionType(static_cast<SceneCamera::ProjectionType>(i));
                }
                if (selected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        switch (camera.getProjectionType()) {
            case SceneCamera::ProjectionType::Perspective:
            {
                float verticalFOV = glm::degrees(camera.getPerspectiveVerticalFOV());
                if (ImGui::DragFloat("Vertical FOV", &verticalFOV)) {
                    camera.setPerspectiveVerticalFOV(glm::radians(verticalFOV));
                }
                float nearClip = camera.getPerspectiveNearClip();
                if (ImGui::DragFloat("Near Clip", &nearClip)) {
                    camera.setPerspectiveNearClip(nearClip);
                }
                float farClip = camera.getPerspectiveFarClip();
                if (ImGui::DragFloat("Far Clip", &farClip)) {
                    camera.setPerspectiveFarClip(farClip);
                }
                break;
            }
            case SceneCamera::ProjectionType::Orthographic:
            {
                float size = camera.getOrthographicSize();
                if (ImGui::DragFloat("Size", &size)) {
                    camera.setOrthographicSize(size);
                }
                float nearClip = camera.getOrthographicNearClip();
                if (ImGui::DragFloat("Near Clip", &nearClip)) {
                    camera.setOrthographicNearClip(nearClip);
                }
                float farClip = camera.getOrthographicFarClip();
                if (ImGui::DragFloat("Far Clip", &farClip)) {
                    camera.setOrthographicFarClip(farClip);
                }
                ImGui::Checkbox("Fixed Aspect Ratio", &component.fixedAspectRatio);
                break;
            }
        }
    });
    entity.drawComponent<SpriteComponent>("Sprite", [&]() {
        auto& color = entity.getComponent<SpriteComponent>().color;
        ImGui::ColorEdit4("Color", glm::value_ptr(color));
    });
}
}
