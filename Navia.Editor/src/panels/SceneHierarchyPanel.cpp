#include "panels/SceneHierarchyPanel.hpp"
#include "navia/scene/Components.hpp"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Navia {
SceneHierarchyPanel:: SceneHierarchyPanel(Ref<Scene> scene) {
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
    if (entity.hasComponent<TagComponent>()) {
        auto& tag = entity.getComponent<TagComponent>().tag;
        char buffer[256];
        std::memset(buffer, 0, sizeof(buffer));
        std::memcpy(buffer, tag.c_str(), sizeof(buffer));
        if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
            tag = std::string{ buffer };
        }
    }
    if (entity.hasComponent<TransformComponent>()) {
        if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(TransformComponent).hash_code()), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
            auto& transform = entity.getComponent<TransformComponent>().transform;
            ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
            ImGui::TreePop();
        }
    }
}
}
