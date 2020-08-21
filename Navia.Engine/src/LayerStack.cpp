#include "navia/core/LayerStack.hpp"

namespace Navia {
LayerStack::~LayerStack() {
    for (auto layer : layers) {
        layer->onDetach();
        delete layer;
    }
}

void LayerStack::pushLayer(Layer* layer) {
    layers.emplace(layers.begin() + layerIndex, layer);
    ++layerIndex;
}

void LayerStack::pushOverlay(Layer* overlay) {
    layers.emplace_back(overlay);
}

void LayerStack::popLayer(Layer* layer) {
    auto it = std::find(layers.begin(), layers.begin() + layerIndex, layer);
    if (it != layers.begin() + layerIndex) {
        layers.erase(it);
        layerIndex--;
    }
}

void LayerStack::popOverlay(Layer* overlay) {
    auto it = std::find(layers.begin() + layerIndex, layers.end(), overlay);
    if (it != layers.end()) {
        layers.erase(it);
    }
}

std::vector<Layer*>::iterator LayerStack::begin() {
    return layers.begin();
}

std::vector<Layer*>::iterator LayerStack::end() {
    return layers.end();
}

std::vector<Layer*>::reverse_iterator LayerStack::rbegin() {
    return layers.rbegin();
}

std::vector<Layer*>::reverse_iterator LayerStack::rend() {
    return layers.rend();
}

std::vector<Layer*>::const_iterator LayerStack::begin() const {
    return layers.begin();
}

std::vector<Layer*>::const_iterator LayerStack::end() const {
    return layers.end();
}

std::vector<Layer*>::const_reverse_iterator LayerStack::rbegin() const {
    return layers.rbegin();
}

std::vector<Layer*>::const_reverse_iterator LayerStack::rend() const {
    return layers.rend();
}
}