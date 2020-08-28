#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include "navia/core/Core.hpp"
#include "navia/core/LayerStack.hpp"
#include "navia/core/Timestep.hpp"
#include "navia/core/Window.hpp"
#include "navia/events/Event.hpp"
#include "navia/events/WindowEvent.hpp"
#include "navia/imgui/ImGuiLayer.hpp"
#include "navia/renderer/Renderer.hpp"

namespace Navia {
class Application {
public:
    Application();
    virtual ~Application();

    static Application& getInstance();
    Window& getWindow() const;

    void run();

    void onEvent(Event& event);

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* overlay);

private:
    static Application* instance;

    Scope<Window> window;
    bool running{ true };
    bool minimized{ false };

    ImGuiLayer* imGuiLayer;
    LayerStack layerStack;
    float lastFrameTime{ 0.0f };

    bool onWindowResize(WindowResizeEvent& event);
    bool onWindowClose(WindowCloseEvent& event);
};

Application* create();
}

#endif