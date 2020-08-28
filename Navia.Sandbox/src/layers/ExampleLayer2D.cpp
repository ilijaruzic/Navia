#include "layers/ExampleLayer2D.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

ExampleLayer2D::ExampleLayer2D() : Navia::Layer("ExampleLayer2D") {}

void ExampleLayer2D::onAttach() {

}

void ExampleLayer2D::onDetach() {

}

void ExampleLayer2D::onImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(blue));
    ImGui::ColorEdit4("Rectangle Color", glm::value_ptr(red));
    ImGui::End();
}

void ExampleLayer2D::onUpdate(Navia::Timestep timestep) {
    cameraController.onUpdate(timestep);

    Navia::RenderCommand::setClearColor(glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f });
    Navia::RenderCommand::clear();

    Navia::Renderer2D::beginScene(cameraController.getCamera());
    Navia::Renderer2D::drawQuad(glm::vec2{ -1.0f,  0.0f }, glm::vec2{ 0.8f, 0.8f }, blue);
    Navia::Renderer2D::drawQuad(glm::vec2{  0.5f, -0.5f }, glm::vec2{ 0.5f, 0.7f }, red);
    Navia::Renderer2D::endScene();
}

void ExampleLayer2D::onEvent(Navia::Event& event) {
    cameraController.onEvent(event);
}
