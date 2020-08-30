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

    scene = createRef<Scene>();

    squareEntity = scene->createEntity("Square");
    squareEntity.addComponent<SpriteComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
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
    auto& tag = squareEntity.getComponent<TagComponent>().tag;
    ImGui::Text("%s", tag.c_str());
    auto& squareColor = squareEntity.getComponent<SpriteComponent>().color;
    ImGui::ColorPicker4("Color", glm::value_ptr(squareColor));
    ImGui::Separator();
    ImGui::End();

    auto statistics = Renderer2D::getStatistics();
    ImGui::Begin("Statistics");
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
        framebuffer->resize(static_cast<uint32_t>(viewportRegion.x), static_cast<uint32_t>(viewportRegion.y));
        viewportSize = glm::vec2{ viewportRegion.x, viewportRegion.y };

        cameraController.onResize(viewportRegion.x, viewportRegion.y);
    }
    uint32_t colorAttachment = framebuffer->getColorAttachment();
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

    framebuffer->bind();

    RenderCommand::setClearColor(glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f });
    RenderCommand::clear();

    Renderer2D::beginScene(cameraController.getCamera());
    scene->onUpdate(timestep);

    Renderer2D::endScene();

    framebuffer->unbind();
}

void EditorLayer::onEvent(Event& event) {
    cameraController.onEvent(event);
}
}