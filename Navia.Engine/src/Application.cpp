#include "navia/core/Application.hpp"
#include <GLFW/glfw3.h>

namespace Navia {
Application* Application::instance{ nullptr };

Application::Application() : window(std::unique_ptr<Window>(Window::create())), imGuiLayer(new ImGuiLayer()) {
    NAVIA_CORE_ASSERT(!instance, "Application already initialized!");
    instance = this;

    window->setEventCallback(NAVIA_BIND_EVENT_CALLBACK(Application::onEvent));

    Renderer::init();

    pushOverlay(imGuiLayer);
}

Application& Application::getInstance() {
    return *instance;
}

Window& Application::getWindow() const {
    return *window;
}

void Application::run() {
    while (running) {
        float time = static_cast<float>(glfwGetTime()); // abstraction needed
        Timestep timestep{ time - lastFrameTime };
        lastFrameTime = time;

        for (auto layer : layerStack) {
            layer->onUpdate(timestep);
        }

        imGuiLayer->begin();
        for (auto layer : layerStack) {
            layer->onImGuiRender();
        }
        imGuiLayer->end();

        window->onUpdate();
    }
}

void Application::onEvent(Event& event) {
    EventDispatcher dispatcher{ event };
    dispatcher.dispatch<WindowCloseEvent>(NAVIA_BIND_EVENT_CALLBACK(Application::onWindowClose));

    for (auto it = layerStack.end(); it != layerStack.begin();) {
        (*--it)->onEvent(event);
        if (event.handled) {
            break;
        }
    }
}

void Application::pushLayer(Layer* layer) {
    layerStack.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer* overlay) {
    layerStack.pushOverlay(overlay);
    overlay->onAttach();
}

bool Application::onWindowClose(WindowCloseEvent& event) {
    running = false;
    return true;
}
}