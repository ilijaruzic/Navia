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

    template <typename Component, bool removable, typename Functor>
    void drawComponent(const std::string& name, Functor functor) {
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;
        if (hasComponent<Component>()) {
            bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(Component).hash_code()), treeNodeFlags, name.c_str());
            bool removed = false;
            if (removable) {
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4.0f, 4.0f} );
                ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
                if (ImGui::Button("+", ImVec2{ 20.0f, 20.0f })) {
                    ImGui::OpenPopup("##ComponentSettings");
                }
                ImGui::PopStyleVar();
                if (ImGui::BeginPopup("##ComponentSettings")) {
                    if (ImGui::MenuItem("Remove component")) {
                        removed = true;
                    }
                    ImGui::EndPopup();
                }
            }
            if (opened) {
                functor();
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