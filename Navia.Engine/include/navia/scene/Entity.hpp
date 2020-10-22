#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include "navia/scene/Scene.hpp"
#include <entt/entt.hpp>
#include <imgui.h>

namespace Navia {
class Entity {
public:
    Entity() = default;
    Entity(entt::entity handle, Scene* scene);

    operator bool() const;
    operator uint32_t() const;
    operator entt::entity() const;

    friend bool operator==(const Entity& lhs, const Entity& rhs);
    friend bool operator!=(const Entity& lhs, const Entity& rhs);


    template <typename Component, typename ... Args>
    Component& addComponent(Args&& ... args) {
        NAVIA_CORE_ASSERT(!hasComponent<Component>(), "Entity already has given component!");
        auto& component = scene->registry.emplace<Component>(handle, std::forward<Args>(args)...);
        scene->onComponentAdded<Component>(*this, component);
        return component;
    }

    template <typename Component>
    Component& getComponent() {
        NAVIA_CORE_ASSERT(hasComponent<Component>(), "Entity does not have given component!");
        return scene->registry.get<Component>(handle);
    }

    template <typename Component>
    bool hasComponent() {
        return scene->registry.has<Component>(handle);
    }

    template <typename Component>
    void removeComponent() {
        NAVIA_CORE_ASSERT(hasComponent<Component>(), "Entity does not have given component!");
        scene->registry.remove<Component>(handle);
    }

    template <typename Component, typename Functor>
    void drawComponent(const std::string& name, Functor functor) {
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen |
                                                 ImGuiTreeNodeFlags_Framed |
                                                 ImGuiTreeNodeFlags_SpanAvailWidth |
                                                 ImGuiTreeNodeFlags_AllowItemOverlap |
                                                 ImGuiTreeNodeFlags_FramePadding;
        if (hasComponent<Component>()) {
            auto& component = getComponent<Component>();
            ImVec2 contentRegionAvail = ImGui::GetContentRegionAvail();
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4.0f, 4.0f });
            float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            ImGui::Separator();
            bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(Component).hash_code()), treeNodeFlags, name.c_str());
            ImGui::PopStyleVar();
            ImGui::SameLine(contentRegionAvail.x - lineHeight * 0.5f);
            if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight })) {
                ImGui::OpenPopup("##ComponentSettings");
            }
            bool removed = false;
            if (ImGui::BeginPopup("##ComponentSettings")) {
                if (ImGui::MenuItem("Remove component")) {
                    removed = true;
                }
                ImGui::EndPopup();
            }
            if (opened) {
                functor(component);
                ImGui::TreePop();
            }
            if (removed) {
                removeComponent<Component>();
            }
        }
    }

private:
    entt::entity handle = entt::null;
    Scene* scene = nullptr;
};
}

#endif