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

    primaryCameraEntity = scene->createEntity("Primary Camera");
    primaryCameraEntity.addComponent<CameraComponent>();

    secondaryCameraEntity = scene->createEntity("Secondary Camera");
    auto& camera = secondaryCameraEntity.addComponent<CameraComponent>();
    camera.primary = false;

    class CameraController : public ScriptableEntity {
    public:
        void onCreate() override {
            auto& transform = getComponent<TransformComponent>().transform;
            transform[3][0] = std::rand() % 10 - 5.0f;
        }

        void onUpdate(Timestep timestep) override {
            auto& transform = getComponent<TransformComponent>().transform;
            float cameraSpeed = 5.0f;
            if (Input::isKeyPressed(Key::A)) {
                transform[3][0] -= cameraSpeed * timestep;
            }
            if (Input::isKeyPressed(Key::D)) {
                transform[3][0] += cameraSpeed * timestep;
            }
            if (Input::isKeyPressed(Key::W)) {
                transform[3][1] += cameraSpeed * timestep;
            }
            if (Input::isKeyPressed(Key::S)) {
                transform[3][1] -= cameraSpeed * timestep;
            }
        }
    };
    primaryCameraEntity.addComponent<NativeScriptComponent>().bind<CameraController>();
    secondaryCameraEntity.addComponent<NativeScriptComponent>().bind<CameraController>();
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
    {
        ImGui::Text("Cameras");
        auto& transform = primaryCameraEntity.getComponent<TransformComponent>().transform[3];
        ImGui::DragFloat3("Primary Camera Transform", glm::value_ptr(transform));
        if (ImGui::Checkbox("Switch Camera", &primary)) {
            primaryCameraEntity.getComponent<CameraComponent>().primary = primary;
            secondaryCameraEntity.getComponent<CameraComponent>().primary = !primary;
        }
        auto& camera = secondaryCameraEntity.getComponent<CameraComponent>().camera;
        float size = camera.getOrthographicSize();
        if (ImGui::DragFloat("Secondary Camera Orthographic Size", &size)) {
            camera.setOrthographicSize(size);
        }
    }
    if (squareEntity) {
        ImGui::Separator();
        auto& tag = squareEntity.getComponent<TagComponent>().tag;
        ImGui::Text("%s", tag.c_str());
        auto& squareColor = squareEntity.getComponent<SpriteComponent>().color;
        ImGui::ColorPicker4("Color", glm::value_ptr(squareColor));
    }
    ImGui::End();

    auto statistics = Renderer2D::getStatistics();
    ImGui::Begin("Statistics");
    ImGui::Text("Draw Calls: %d", statistics.drawCallCount);
    ImGui::Text("Quads: %d", statistics.quadCount);
    ImGui::Text("Vertices: %d", statistics.getVertexCount());
    ImGui::Text("Indices: %d", statistics.getIndexCount());
    ImGui::End();

    auto info = Renderer2D::getInfo();
    ImGui::Begin("OpenGL Information");
    ImGui::Text("Vendor: %s",   info.vendor);
    ImGui::Text("Renderer: %s", info.renderer);
    ImGui::Text("Version: %s",  info.version);
    ImGui::End();

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
}
}