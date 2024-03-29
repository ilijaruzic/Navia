#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include "navia/core/Timestep.hpp"
#include "navia/events/Event.hpp"

namespace Navia {
class Layer {
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    std::string getName() const;

    virtual void onAttach();
    virtual void onDetach();
    virtual void onImGuiRender();
    virtual void onUpdate(Timestep timestep);
    virtual void onEvent(Event& event);

private:
    std::string name;
};
}

#endif