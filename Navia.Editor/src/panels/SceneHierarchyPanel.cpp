#include "panels/SceneHierarchyPanel.hpp"
#include "navia/scene/Components.hpp"
#include <imgui.h>
#include <imgui_internal.h>
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
    if (ImGui::BeginPopupContextWindow(0, 1, false)) {
        if (ImGui::MenuItem("Create empty entity")) {
            scene->createEntity("Empty entity");
        }
        ImGui::EndPopup();
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
    ImGuiTreeNodeFlags flags = (selectedEntity == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
    bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>(static_cast<uint64_t>(static_cast<uint32_t>(entity))), flags, "%s", tag.c_str());
    if (ImGui::IsItemClicked()) {
        selectedEntity = entity;
    }
    bool deleted = false;
    if (ImGui::BeginPopupContextItem()) {
        if (ImGui::MenuItem("Delete entity")) {
            deleted = true;
        }
        ImGui::EndPopup();
    }
    if (opened) {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth ;
        bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>(9817239), flags, "%s", tag.c_str());
        if (opened) {
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
    if (deleted) {
        scene->destroyEntity(entity);
        if (selectedEntity == entity) {
            selectedEntity = Entity{};
        }
    }
}

static void drawVec3Control(const std::string& label, glm::vec3& values, float initialValue = 0.0f, float columnWidth = 100.0f) {
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y + 2.0f;
    ImVec2 buttonSize{ lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize)) {
        values.x = initialValue;
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize)) {
        values.y = initialValue;
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.3f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.4f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.3f, 0.8f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Z", buttonSize)) {
        values.z = initialValue;
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();
}

void SceneHierarchyPanel::drawEntityComponents(Entity entity) {
    if (entity.hasComponent<TagComponent>()) {
        auto& tag = entity.getComponent<TagComponent>().tag;
        char buffer[256];
        std::memset(buffer, 0, sizeof(buffer));
        std::memcpy(buffer, tag.c_str(), sizeof(buffer));
        if (ImGui::InputText("##TagComponent", buffer, sizeof(buffer))) {
            tag = std::string{ buffer };
        }
    };
    ImGui::SameLine();
    ImGui::PushItemWidth(-1);
    if (ImGui::Button("Add component")) {
        ImGui::OpenPopup("##AddComponent");
    }
    if (ImGui::BeginPopup("##AddComponent")) {
        if (ImGui::MenuItem("Camera")) {
            selectedEntity.addComponent<CameraComponent>();
            ImGui::CloseCurrentPopup();
        }
        if (ImGui::MenuItem("Sprite")) {
            selectedEntity.addComponent<SpriteComponent>();
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    ImGui::PopItemWidth();
    entity.drawComponent<TransformComponent>("Transform", [&](auto& component) {
        drawVec3Control("Translation", component.translation);
        glm::vec3 rotation = glm::degrees(component.rotation);
        drawVec3Control("Rotation", rotation);
        component.rotation = glm::radians(rotation);
        drawVec3Control("Scale", component.scale, 1.0f);
    });
    entity.drawComponent<CameraComponent>("Camera", [&](auto& component) {
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
    entity.drawComponent<SpriteComponent>("Sprite", [&](auto& component) {
        ImGui::ColorEdit4("Color", glm::value_ptr(component.color));
    });
}
}
