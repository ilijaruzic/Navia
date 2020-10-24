#ifndef _EDITOR_LAYER_HPP_
#define _EDITOR_LAYER_HPP_

#include "panels/SceneHierarchyPanel.hpp"
#include <Navia.hpp>

namespace Navia {
class EditorLayer : public Layer {
public:
    EditorLayer();

    void onAttach() override;
    void onDetach() override;
    void onImGuiRender() override;
    void onUpdate(Timestep timestep) override;
    void onEvent(Event& event) override;

private:
    OrthographicCameraController cameraController{ 1280.0f / 720.0f, true };

    Ref<Framebuffer> framebuffer;
    Ref<Shader> shader;
    Ref<VertexArray> vertexArray;
    Ref<Scene> scene;
    Entity greenSquareEntity;
    Entity redSquareEntity;
    Entity primaryCameraEntity;
    Entity secondaryCameraEntity;
    bool primary = true;

    bool viewportFocused = false;
    bool viewportHovered = false;
    glm::vec2 viewportSize{ 0.0f };

    SceneHierarchyPanel sceneHierarchyPanel;

    bool onKeyPressed(KeyPressedEvent& event);
    void newScene();
    void openScene();
    void saveSceneAs();
    void close();
};
}

#endif