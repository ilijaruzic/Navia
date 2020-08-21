#ifndef _IMGUI_LAYER_HPP_
#define _IMGUI_LAYER_HPP_

#include "Layer.hpp"
#include "MouseEvent.hpp"
#include "KeyEvent.hpp"
#include "WindowEvent.hpp"

namespace Navia {
class ImGuiLayer : public Layer {
public:
    ImGuiLayer();

    void onAttach() override;
    void onDetach() override;
    void onImGuiRender() override;

    void begin();
    void end();

private:
    float time{};
};
}

#endif