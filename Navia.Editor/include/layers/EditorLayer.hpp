#ifndef _EDITOR_LAYER_HPP_
#define _EDITOR_LAYER_HPP_

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

    glm::vec4 red{ 0.8f, 0.2f, 0.0f, 1.0f };
    glm::vec4 green{ 0.2f, 0.8f, 0.2f, 1.0f };
    glm::vec4 blue{ 0.0f, 0.2f, 0.8f, 1.0f };
    float bigCheckerboardTextureResolution{ 5.0f };
    float smallCheckerboardTextureRotation{ 0.0f };
    float smallCheckerboardTextureResolution{ 15.0f };

    Ref<Framebuffer> framebuffer;
    Ref<Shader> shader;
    Ref<VertexArray> vertexArray;
    Ref<Texture2D> checkerboardTexture;

    bool viewportFocused{ false };
    bool viewportHovered{ false };
    glm::vec2 viewportSize{ 0.0f };
};
}

#endif