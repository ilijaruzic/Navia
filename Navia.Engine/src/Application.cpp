#include "Application.hpp"
#include <glad/glad.h>

namespace Navia {
Application* Application::instance{ nullptr };

Application::Application() : window(std::unique_ptr<Window>(Window::create())), imGuiLayer(new ImGuiLayer()) {
    NAVIA_CORE_ASSERT(!instance, "Application already initialized!");
    instance = this;

    window->setEventCallback(NAVIA_BIND_EVENT_CALLBACK(Application::onEvent));

    pushOverlay(imGuiLayer);
}

Application::~Application() {}

Application& Application::getInstance() {
    return *instance;
}

Window& Application::getWindow() const {
    return *window;
}

void Application::run() {
    NAVIA_TRACE("Hello Sandbox!");

    while (running) {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto layer : layerStack) {
            layer->onUpdate();
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