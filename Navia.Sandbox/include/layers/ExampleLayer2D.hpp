#ifndef _EXAMPLE_LAYER_2D_HPP_
#define _EXAMPLE_LAYER_2D_HPP_

#include <Navia.hpp>

class ExampleLayer2D : public Navia::Layer {
public:
    ExampleLayer2D();

    void onAttach() override;
    void onDetach() override;
    void onImGuiRender() override;
    void onUpdate(Navia::Timestep timestep) override;
    void onEvent(Navia::Event& event) override;

private:
    Navia::OrthographicCameraController cameraController{ 1280.0f / 720.0f, true };

    glm::vec4 blue{ 0.0f, 0.2f, 0.8f, 1.0f };
    glm::vec4 red{ 0.8f, 0.2f, 0.0f, 1.0f };
    float checkerboardTextureResolution{ 5.0f };
    float googleTextureRotation{ 0.0f };

    // Temporary
    Navia::Ref<Navia::Shader> shader;
    Navia::Ref<Navia::VertexArray> vertexArray;
    Navia::Ref<Navia::Texture2D> checkerboardTexture;
    Navia::Ref<Navia::Texture2D> googleTexture;
};

#endif