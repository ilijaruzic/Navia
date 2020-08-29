#include "layers/EditorLayer.hpp"
#include "EditorApplication.hpp"
#include <NaviaEntrypoint.hpp>

namespace Navia {
Application* create() {
    return new EditorApplication();
}

EditorApplication::EditorApplication() : Application("Navia Editor") {
    pushLayer(new EditorLayer());
}

EditorApplication::~EditorApplication() {}
}