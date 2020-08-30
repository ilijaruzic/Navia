#include "panels/SceneHierarchyPanel.hpp"
#include "navia/scene/Components.hpp"
#include <imgui.h>

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
}
