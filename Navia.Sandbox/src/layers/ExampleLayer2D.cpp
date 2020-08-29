#include "layers/ExampleLayer2D.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

ExampleLayer2D::ExampleLayer2D() : Navia::Layer("ExampleLayer2D") {}

void ExampleLayer2D::onAttach() {
    NAVIA_PROFILE_FUNCTION();

    checkerboardTexture = Navia::Texture2D::create("assets/textures/checkerboard.png");
}

void ExampleLayer2D::onDetach() {
    NAVIA_PROFILE_FUNCTION();


}

void ExampleLayer2D::onImGuiRender() {
    NAVIA_PROFILE_FUNCTION();


    ImGui::Begin("Settings");
    ImGui::SetWindowSize(ImVec2(400.0f, 200.0f));
    ImGui::ColorEdit4("S-Color", glm::value_ptr(blue));
    ImGui::ColorEdit4("R-Color", glm::value_ptr(red));
    ImGui::SliderFloat("BCT-Resolution", &bigCheckerboardTextureResolution, 1.0f, 10.0f);
    ImGui::SliderFloat("SCT-Rotation", &smallCheckerboardTextureRotation, 0.0f, 360.0f);
    ImGui::SliderFloat("SCT-Resolution", &smallCheckerboardTextureResolution, 10.0f, 20.0f);
    ImGui::End();

    auto statistics = Navia::Renderer2D::getStatistics();
    ImGui::Begin("Statistics");
    ImGui::SetWindowSize(ImVec2(200.0f, 200.0f));
    ImGui::Text("Draw Calls: %d", statistics.drawCallCount);
    ImGui::Text("Quads: %d", statistics.quadCount);
    ImGui::Text("Vertices: %d", statistics.getVertexCount());
    ImGui::Text("Indices: %d", statistics.getIndexCount());
    ImGui::End();
}

void ExampleLayer2D::onUpdate(Navia::Timestep timestep) {
    NAVIA_PROFILE_FUNCTION();

    cameraController.onUpdate(timestep);

    Navia::Renderer2D::resetStatistics();
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
        Navia::Renderer2D::drawQuad(glm::vec2{ -1.0f, 0.0f }, glm::vec2{ 0.8f, 0.8f }, red);
        Navia::Renderer2D::drawQuad(glm::vec2{  1.0f, 0.5f }, glm::vec2{ 0.8f, 0.4f }, green);
        Navia::Renderer2D::drawRotatedQuad(glm::vec2{ 0.5f, -0.5f }, glm::vec2{ 0.5f, 0.7f }, rectangleRotation, blue);
        Navia::Renderer2D::drawQuad(glm::vec3{ 0.0f, 0.0f, -0.1f }, glm::vec2{ 20.0f, 20.0f }, checkerboardTexture, bigCheckerboardTextureResolution);
        Navia::Renderer2D::drawRotatedQuad(glm::vec3{ -2.0f, 0.0f, 0.0f }, glm::vec2{  1.0f,  1.0f }, smallCheckerboardTextureRotation, checkerboardTexture, smallCheckerboardTextureResolution);
        Navia::Renderer2D::endScene();

        Navia::Renderer2D::beginScene(cameraController.getCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.5f) {
            for (float x = -5.0f; x < 5.0f; x += 0.5f) {
                glm::vec4 color{ (x + 5.0f) / 10.0f, 0.5f, (y + 5.0f) / 10.0f, 0.75f };
                Navia::Renderer2D::drawQuad(glm::vec2{ x, y }, glm::vec2{ 0.45f, 0.45f }, color);
            }
        }
        Navia::Renderer2D::endScene();
    }
}

void ExampleLayer2D::onEvent(Navia::Event& event) {
    cameraController.onEvent(event);
}
