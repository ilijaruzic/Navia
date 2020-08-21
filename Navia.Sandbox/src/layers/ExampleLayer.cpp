#include "ExampleLayer.hpp"

ExampleLayer::ExampleLayer() : Navia::Layer("ExampleLayer") {}

void ExampleLayer::onUpdate() {
    if (Navia::Input::isKeyPressed(NAVIA_KEY_TAB)) {
        NAVIA_INFO("Tab key is pressed! (poll)");
    }
}

void ExampleLayer::onEvent(Navia::Event& event) {
    if (event.getEventType() == Navia::EventType::KeyPressed) {
        Navia::KeyPressedEvent& e = static_cast<Navia::KeyPressedEvent&>(event);
        if (e.getKeyCode() == NAVIA_KEY_TAB) {
            NAVIA_INFO("Tab key is pressed! (event)");
        }
        NAVIA_TRACE("{0}", static_cast<char>(e.getKeyCode()));
    }
}