#include "layers/EditorLayer.hpp"
#include "navia/scene/SceneSerializer.hpp"
#include "navia/utils/PlatformUtils.hpp"
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
    sceneHierarchyPanel.setContext(scene);
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
    ImGuiStyle& style = ImGui::GetStyle();
    float windowMinSizeX = style.WindowMinSize.x;
    style.WindowMinSize.x = 370.0f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspaceId = ImGui::GetID("Dockspace");
        ImGui::DockSpace(dockspaceId, ImVec2{ 0.0f, 0.0f }, dockspaceFlags);
    }
    style.WindowMinSize.x = windowMinSizeX;
    bool openInfo = false;
    bool openStats = false;
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New", "Ctrl+N")) {
                newScene();
            }
            if (ImGui::MenuItem("Open...", "Ctrl+O")) {
                openScene();
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {
                saveSceneAs();
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) {
                close();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("About")) {
            if (ImGui::MenuItem("OpenGL Information")) {
                openInfo = true;
            }
            if (ImGui::MenuItem("Statistics")) {
                openStats = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    auto info = Renderer2D::getInfo();
    if (openInfo) {
        ImGui::OpenPopup("OpenGL Information");
    }
    if (ImGui::BeginPopup("OpenGL Information")) {
        ImGui::Text("Vendor: %s", info.vendor);
        ImGui::Text("Renderer: %s", info.renderer);
        ImGui::Text("Version: %s", info.version);
        ImGui::EndPopup();
    }
    auto statistics = Renderer2D::getStatistics();
    if (openStats) {
        ImGui::OpenPopup("Statistics");
    }
    if (ImGui::BeginPopup("Statistics")) {
        ImGui::Text("Draw Calls: %d", statistics.drawCallCount);
        ImGui::Text("Quads: %d", statistics.quadCount);
        ImGui::Text("Vertices: %d", statistics.getVertexCount());
        ImGui::Text("Indices: %d", statistics.getIndexCount());
        ImGui::EndPopup();
    }

    sceneHierarchyPanel.onImGuiRender();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
    ImGui::Begin("Viewport");
    viewportFocused = ImGui::IsWindowFocused();
    viewportHovered = ImGui::IsWindowHovered();
    Application::getInstance().getImGuiLayer()->setBlockEvents(!(viewportFocused && viewportHovered));
    ImVec2 viewportRegion = ImGui::GetContentRegionAvail();
    viewportSize = glm::vec2{ viewportRegion.x, viewportRegion.y };
    uint32_t colorAttachment = framebuffer->getColorAttachment();
    ImGui::Image(reinterpret_cast<void*>(colorAttachment), ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
    ImGui::End();
    ImGui::PopStyleVar();

    ImGui::End();
}

void EditorLayer::onUpdate(Timestep timestep) {
    NAVIA_PROFILE_FUNCTION();

    if (auto properties = framebuffer->getProperties();
        viewportSize.x > 0.0f && viewportSize.y > 0.0f &&
        (properties.width != viewportSize.x || properties.height != viewportSize.y)) {
        framebuffer->resize(static_cast<uint32_t>(viewportSize.x), static_cast<uint32_t>(viewportSize.y));
        cameraController.onResize(viewportSize.x, viewportSize.y);
        scene->onViewportResize(static_cast<uint32_t>(viewportSize.x), static_cast<uint32_t>(viewportSize.y));
    }

    if (viewportFocused) {
        cameraController.onUpdate(timestep);
    }

    Renderer2D::resetStatistics();

    framebuffer->bind();

    RenderCommand::setClearColor(glm::vec4{ 0.1f, 0.1f, 0.1f, 1.0f });
    RenderCommand::clear();

    scene->onUpdate(timestep);

    framebuffer->unbind();
}

void EditorLayer::onEvent(Event& event) {
    cameraController.onEvent(event);
    EventDispatcher dispatcher{ event };
    dispatcher.dispatch<KeyPressedEvent>(NAVIA_BIND_EVENT_CALLBACK(EditorLayer::onKeyPressed));
}

bool EditorLayer::onKeyPressed(KeyPressedEvent& event) {
    if (event.getRepeatCount() > 0) {
        return false;
    }
    bool alt = Input::isKeyPressed(Key::LeftAlt) || Input::isKeyPressed(Key::RightAlt);
    bool ctrl = Input::isKeyPressed(Key::LeftControl) || Input::isKeyPressed(Key::RightControl);
    bool shift = Input::isKeyPressed(Key::LeftShift) || Input::isKeyPressed(Key::RightShift);
    switch (event.getKeyCode()) {
        case Key::N: {
            if (ctrl) {
                newScene();
            }
            break;
        }
        case Key::O: {
            if (ctrl) {
                openScene();
            }
            break;
        }
        case Key::S: {
            if (ctrl && shift) {
                saveSceneAs();
            }
            break;
        }
        case Key::F4: {
            if (alt) {
                close();
            }
            break;
        }
    }
}

void EditorLayer::newScene() {
    scene = createRef<Scene>();
    scene->onViewportResize(static_cast<uint32_t>(viewportSize.x), static_cast<uint32_t>(viewportSize.y));
    sceneHierarchyPanel.setContext(scene);
}

void EditorLayer::openScene() {
    std::string filepath = FileDialog::openFile("Navia Scene (*.navia)\0*.navia\0");
    if (!filepath.empty()) {
        newScene();
        SceneSerializer serializer{ scene };
        serializer.deserialize(filepath, SceneSerializer::Mode::Text);
    }
}

void EditorLayer::saveSceneAs() {
    std::string filepath = FileDialog::saveFile("Navia Scene (*.navia)\0*.navia\0");
    if (!filepath.empty()) {
        SceneSerializer serializer{scene};
        serializer.serialize(filepath, SceneSerializer::Mode::Text);
    }
}

void EditorLayer::close() {
    Application::getInstance().close();
}


}