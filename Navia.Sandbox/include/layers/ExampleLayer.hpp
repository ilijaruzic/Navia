#ifndef _EXAMPLE_LAYER_HPP_
#define _EXAMPLE_LAYER_HPP_

#include <Navia.hpp>

class ExampleLayer : public Navia::Layer {
public:
    ExampleLayer();

    void onUpdate() override;
    void onEvent(Navia::Event& event) override;
};

#endif