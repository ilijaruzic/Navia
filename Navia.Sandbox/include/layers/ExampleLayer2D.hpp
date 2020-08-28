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

    glm::vec4 squareColor{ 0.0f, 0.5f, 0.75f, 1.0f };

    // Temporary
    Navia::Ref<Navia::Shader> shader;
    Navia::Ref<Navia::VertexArray> vertexArray;
};

#endif