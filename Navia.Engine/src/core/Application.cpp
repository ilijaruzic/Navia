#include "navia/core/Application.hpp"
#include <GLFW/glfw3.h>

namespace Navia {
Application* Application::instance = nullptr;

Application::Application(const std::string& name) : window(std::unique_ptr<Window>(Window::create(WindowProperties{ name }))), imGuiLayer(new ImGuiLayer()) {
    NAVIA_PROFILE_FUNCTION();

    NAVIA_CORE_ASSERT(!instance, "Application already initialized!");
    instance = this;

    window->setEventCallback(NAVIA_BIND_EVENT_CALLBACK(Application::onEvent));

    Renderer::init();

    pushOverlay(imGuiLayer);
}

Application::~Application() {
    NAVIA_PROFILE_FUNCTION();

    Renderer::shutdown();
}

Application& Application::getInstance() {
    return *instance;
}

Window& Application::getWindow() const {
    return *window;
}

ImGuiLayer* Application::getImGuiLayer() {
    return imGuiLayer;
}

void Application::run() {
    NAVIA_PROFILE_FUNCTION();

    while (running) {
        NAVIA_PROFILE_SCOPE("Navia::Application::run — main loop");

        float time = static_cast<float>(glfwGetTime()); // abstraction needed
        Timestep timestep{ time - lastFrameTime };
        lastFrameTime = time;

        if (!minimized) {
            {
                NAVIA_PROFILE_SCOPE("Navia::Application::run — layer stack onUpdate()");

                for (auto layer : layerStack) {
                    layer->onUpdate(timestep);
                }
            }
        }

        imGuiLayer->begin();
        {
            NAVIA_PROFILE_SCOPE("Navia::Application::run — layer stack onImGuiRender()");

            for (auto layer : layerStack) {
                layer->onImGuiRender();
            }
        }
        imGuiLayer->end();

        window->onUpdate();
    }
}

void Application::onEvent(Event& event) {
    NAVIA_PROFILE_FUNCTION();

    EventDispatcher dispatcher{ event };
    dispatcher.dispatch<WindowResizeEvent>(NAVIA_BIND_EVENT_CALLBACK(Application::onWindowResize));
    dispatcher.dispatch<WindowCloseEvent>(NAVIA_BIND_EVENT_CALLBACK(Application::onWindowClose));

    for (auto it = layerStack.end(); it != layerStack.begin();) {
        (*--it)->onEvent(event);
        if (event.handled) {
            break;
        }
    }
}

void Application::close() {
    running = false;
}

void Application::pushLayer(Layer* layer) {
    NAVIA_PROFILE_FUNCTION();

    layerStack.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer* overlay) {
    NAVIA_PROFILE_FUNCTION();

    layerStack.pushOverlay(overlay);
    overlay->onAttach();
}

bool Application::onWindowResize(WindowResizeEvent& event) {
    NAVIA_PROFILE_FUNCTION();

    if (event.getWidth() == 0 || event.getHeight() == 0) {
        minimized = true;
        return false;
    }
    minimized = false;
    Renderer::onWindowResize(event.getWidth(), event.getHeight());
    return false;
}

bool Application::onWindowClose(WindowCloseEvent& event) {
    running = false;
    return true;
}
}