#include "layers/ExampleLayer.hpp"
#include "layers/ExampleLayer2D.hpp"
#include "SandboxApplication.hpp"
#include <NaviaEntrypoint.hpp>

Navia::Application* Navia::create() {
    return new SandboxApplication();
}

SandboxApplication::SandboxApplication() {
    NAVIA_TRACE("Hello Sandbox!");
    // pushLayer(new ExampleLayer());
    pushLayer(new ExampleLayer2D());
}

SandboxApplication::~SandboxApplication() {}