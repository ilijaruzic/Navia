#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include "Event.hpp"

namespace Navia {
class Layer {
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    std::string getName() const;

    virtual void onAttach();
    virtual void onDetach();
    virtual void onImGuiRender();
    virtual void onUpdate();
    virtual void onEvent(Event& event);

private:
    std::string name;
};
}

#endif