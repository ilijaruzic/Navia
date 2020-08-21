#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include "navia/core/Core.hpp"
#include "navia/core/LayerStack.hpp"
#include "navia/core/Window.hpp"
#include "navia/events/Event.hpp"
#include "navia/events/WindowEvent.hpp"
#include "navia/imgui/ImGuiLayer.hpp"

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
    std::unique_ptr<Window> window;
    ImGuiLayer* imGuiLayer;
    bool running{ true };
    LayerStack layerStack;

    bool onWindowClose(WindowCloseEvent& event);
};

Application* create();
}

#endif