#include "layers/EditorLayer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Navia {
EditorLayer::EditorLayer() : Layer("EditorLayer") {}

void EditorLayer::onAttach() {
    NAVIA_PROFILE_FUNCTION();

    FramebufferProperties properties{
        .width = 1280,
        .height = 720
    };
    framebuffer = Framebuffer::create(properties);
    checkerboardTexture = Texture2D::create("assets/textures/checkerboard.png");

    cameraController.setZoomLevel(5.0f);
}

void EditorLayer::onDetach() {
    NAVIA_PROFILE_FUNCTION();


}

void EditorLayer::onImGuiRender() {
    NAVIA_PROFILE_FUNCTION();

    static bool dockspaceOpen{ true };
    static bool dockspaceFullscreen{ true };
    static bool dockspacePadding{ false };
    static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (dockspaceFullscreen) {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else {
        dockspaceFlags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }
    if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) {
        windowFlags |= ImGuiWindowFlags_NoBackground;
    }
    if (!dockspacePadding) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
    }
    ImGui::Begin("Dockspace", &dockspaceOpen, windowFlags);
    if (!dockspacePadding) {
        ImGui::PopStyleVar();
    }
    if (dockspaceFullscreen) {
        ImGui::PopStyleVar(2);
    }
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspaceId = ImGui::GetID("Dockspace");
        ImGui::DockSpace(dockspaceId, ImVec2{ 0.0f, 0.0f }, dockspaceFlags);
    }
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) {
                Application::getInstance().close();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::Begin("Settings");
    ImGui::SetWindowSize(ImVec2{ 400.0f, 200.0f });
    ImGui::ColorEdit4("S-Color", glm::value_ptr(blue));
    ImGui::ColorEdit4("R-Color", glm::value_ptr(red));
    ImGui::SliderFloat("BCT-Resolution", &bigCheckerboardTextureResolution, 1.0f, 10.0f);
    ImGui::SliderFloat("SCT-Rotation", &smallCheckerboardTextureRotation, 0.0f, 360.0f);
    ImGui::SliderFloat("SCT-Resolution", &smallCheckerboardTextureResolution, 10.0f, 20.0f);
    ImGui::End();

    auto statistics = Renderer2D::getStatistics();
    ImGui::Begin("Statistics");
    ImGui::SetWindowSize(ImVec2(200.0f, 200.0f));
    ImGui::Text("Draw Calls: %d", statistics.drawCallCount);
    ImGui::Text("Quads: %d", statistics.quadCount);
    ImGui::Text("Vertices: %d", statistics.getVertexCount());
    ImGui::Text("Indices: %d", statistics.getIndexCount());
    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
    ImGui::Begin("Viewport");
    viewportFocused = ImGui::IsWindowFocused();
    viewportHovered = ImGui::IsWindowHovered();
    Application::getInstance().getImGuiLayer()->setBlockEvents(!(viewportFocused && viewportHovered));
    ImVec2 viewportRegion = ImGui::GetContentRegionAvail();
    if (viewportSize != *((glm::vec2*)&viewportRegion) && !(viewportRegion.x <= 0 || viewportRegion.y <= 0)) {
        framebuffer->resize(static_cast<size_t>(viewportRegion.x), static_cast<size_t>(viewportRegion.y));
        viewportSize = glm::vec2{ viewportRegion.x, viewportRegion.y };

        cameraController.onResize(viewportRegion.x, viewportRegion.y);
    }
    size_t colorAttachment = framebuffer->getColorAttachment();
    ImGui::Image((void*)colorAttachment, ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
    ImGui::End();
    ImGui::PopStyleVar();

    ImGui::End();
}

void EditorLayer::onUpdate(Timestep timestep) {
    NAVIA_PROFILE_FUNCTION();

    if (viewportFocused) {
        cameraController.onUpdate(timestep);
    }

    Renderer2D::resetStatistics();
    {
        NAVIA_PROFILE_SCOPE("RenderCommand initial setup");

        framebuffer->bind();
        RenderCommand::setClearColor(glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f });
        RenderCommand::clear();
    }

    {
        NAVIA_PROFILE_SCOPE("Renderere2D draws");

        static float rectangleRotation{ 0.0f };
        rectangleRotation += timestep * 50.0f;

        Renderer2D::beginScene(cameraController.getCamera());
        Renderer2D::drawQuad(glm::vec2{ -1.0f, 0.0f }, glm::vec2{ 0.8f, 0.8f }, red);
        Renderer2D::drawQuad(glm::vec2{  1.0f, 0.5f }, glm::vec2{ 0.8f, 0.4f }, green);
        Renderer2D::drawRotatedQuad(glm::vec2{ 0.5f, -0.5f }, glm::vec2{ 0.5f, 0.7f }, glm::radians(rectangleRotation), blue);
        Renderer2D::drawQuad(glm::vec3{ 0.0f, 0.0f, -0.1f }, glm::vec2{ 20.0f, 20.0f }, checkerboardTexture, bigCheckerboardTextureResolution);
        Renderer2D::drawRotatedQuad(glm::vec3{ -2.0f, 0.0f, 0.0f }, glm::vec2{  1.0f,  1.0f }, glm::radians(smallCheckerboardTextureRotation), checkerboardTexture, smallCheckerboardTextureResolution);
        Renderer2D::endScene();

        Renderer2D::beginScene(cameraController.getCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.5f) {
            for (float x = -5.0f; x < 5.0f; x += 0.5f) {
                glm::vec4 color{ (x + 5.0f) / 10.0f, 0.5f, (y + 5.0f) / 10.0f, 0.75f };
                Renderer2D::drawQuad(glm::vec2{ x, y }, glm::vec2{ 0.45f, 0.45f }, color);
            }
        }
        Renderer2D::endScene();
        framebuffer->unbind();
    }

    Renderer2D::endScene();
}

void EditorLayer::onEvent(Event& event) {
    cameraController.onEvent(event);
}
}