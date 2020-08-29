#include "layers/ExampleLayer2D.hpp"
#include "SandboxApplication.hpp"
#include <NaviaEntrypoint.hpp>

Navia::Application* Navia::create() {
    return new SandboxApplication();
}

SandboxApplication::SandboxApplication() : Navia::Application("Navia Sandbox") {
    pushLayer(new ExampleLayer2D());
}

SandboxApplication::~SandboxApplication() {}