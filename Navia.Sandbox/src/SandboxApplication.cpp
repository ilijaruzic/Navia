#include "ExampleLayer.hpp"
#include "SandboxApplication.hpp"
#include <NaviaEntrypoint.hpp>

Navia::Application* Navia::create() {
    return new SandboxApplication();
}

SandboxApplication::SandboxApplication() {
    pushLayer(new ExampleLayer());
}

SandboxApplication::~SandboxApplication() {}