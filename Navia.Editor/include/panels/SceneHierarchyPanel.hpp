#ifndef _SCENE_HIERARCHY_PANEL_HPP_
#define _SCENE_HIERARCHY_PANEL_HPP_

#include "navia/scene/Entity.hpp"
#include "navia/scene/Scene.hpp"

namespace Navia {
class SceneHierarchyPanel {
public:
    SceneHierarchyPanel() = default;
    SceneHierarchyPanel(Ref<Scene> scene);

    void setContext(Ref<Scene> scene);

    void onImGuiRender();

private:
    Ref<Scene> scene;
    Entity selectedEntity;

    void drawEntityNode(Entity entity);
    void drawEntityComponents(Entity entity);
};
}

#endif