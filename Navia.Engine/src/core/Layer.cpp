#include "navia/core/Layer.hpp"

namespace Navia {
Layer::Layer(const std::string& name) : name(name) {}

Layer::~Layer() {}

std::string Layer::getName() const {
    return name;
}

void Layer::onAttach() {}

void Layer::onDetach() {}

void Layer::onImGuiRender() {}

void Layer::onUpdate(Timestep timestep) {}

void Layer::onEvent(Event& event) {}
}