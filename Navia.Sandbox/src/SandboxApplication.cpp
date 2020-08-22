#include "SandboxApplication.hpp"
#include "layers/ExampleLayer.hpp"
#include <NaviaEntrypoint.hpp>

Navia::Application* Navia::create() {
    return new SandboxApplication();
}

SandboxApplication::SandboxApplication() {
    NAVIA_TRACE("Hello Sandbox!");
    pushLayer(new ExampleLayer());
}

SandboxApplication::~SandboxApplication() {}