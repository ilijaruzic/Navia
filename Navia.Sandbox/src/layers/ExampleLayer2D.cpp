#include "layers/ExampleLayer2D.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

ExampleLayer2D::ExampleLayer2D() : Navia::Layer("ExampleLayer2D") {}

void ExampleLayer2D::onAttach() {
    NAVIA_PROFILE_FUNCTION();

    checkerboardTexture = Navia::Texture2D::create("assets/textures/checkerboard.png");
    googleTexture = Navia::Texture2D::create("assets/textures/google.png");
}

void ExampleLayer2D::onDetach() {
    NAVIA_PROFILE_FUNCTION();


}

void ExampleLayer2D::onImGuiRender() {
    NAVIA_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(blue));
    ImGui::ColorEdit4("Rectangle Color", glm::value_ptr(red));
    ImGui::SliderFloat("Checkerboard Texture Resolution", &checkerboardTextureResolution, 1.0f, 10.0f);
    ImGui::SliderFloat("Google Texture Rotation", &googleTextureRotation, 0.0f, 360.0f);
    ImGui::End();
}

void ExampleLayer2D::onUpdate(Navia::Timestep timestep) {
    NAVIA_PROFILE_FUNCTION();

    cameraController.onUpdate(timestep);

    {
        NAVIA_PROFILE_SCOPE("Navia::RenderCommand initial setup");

        Navia::RenderCommand::setClearColor(glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f });
        Navia::RenderCommand::clear();
    }

    {
        NAVIA_PROFILE_SCOPE("Navia::Renderere2D draws");

        static float rectangleRotation{ 0.0f };
        rectangleRotation += timestep * 50.0f;

        Navia::Renderer2D::beginScene(cameraController.getCamera());
        Navia::Renderer2D::drawQuad(glm::vec2{ -1.0f,  0.0f }, glm::vec2{ 0.8f, 0.8f }, blue);
        Navia::Renderer2D::drawRotatedQuad(glm::vec2{ 0.5f, -0.5f }, glm::vec2{ 0.5f, 0.7f }, rectangleRotation, red);
        Navia::Renderer2D::drawQuad(glm::vec3{ 0.0f, 0.0f, -0.1f }, glm::vec2{ 10.0f, 10.0f }, checkerboardTexture, checkerboardTextureResolution);
        Navia::Renderer2D::drawRotatedQuad(glm::vec3{ -2.0f, 0.0f, 0.0f }, glm::vec2{  1.0f,  1.0f }, googleTextureRotation, googleTexture);
        Navia::Renderer2D::endScene();
    }
}

void ExampleLayer2D::onEvent(Navia::Event& event) {
    cameraController.onEvent(event);
}
