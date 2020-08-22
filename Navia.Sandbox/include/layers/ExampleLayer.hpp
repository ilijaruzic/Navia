#ifndef _EXAMPLE_LAYER_HPP_
#define _EXAMPLE_LAYER_HPP_

#include <Navia.hpp>

class ExampleLayer : public Navia::Layer {
public:
    ExampleLayer();

    void onImGuiRender() override;
    void onUpdate(Navia::Timestep timestep) override;
    void onEvent(Navia::Event& event) override;

private:
    Navia::OrthographicCamera camera{ -1.6f, 1.6f, -0.9f, 0.9f };
    glm::vec3 cameraPosition{ 0.0f };
    float cameraMovementSpeed{ 5.0f };
    float cameraRotation{ 0.0f };
    float cameraRotationSpeed{ 180.0f };

    glm::vec4 squareColor{ 0.0f, 0.5f, 0.75f, 1.0f };

    Navia::ShaderLibrary shaderLibrary;
    Navia::Ref<Navia::Shader> triangleShader;
    Navia::Ref<Navia::Shader> squareFlatColorShader;
    Navia::Ref<Navia::Texture2D> checkerboardTexture;
    Navia::Ref<Navia::Texture2D> googleTexture;
    Navia::Ref<Navia::VertexArray> triangleVertexArray;
    Navia::Ref<Navia::VertexArray> squareVertexArray;
};

#endif