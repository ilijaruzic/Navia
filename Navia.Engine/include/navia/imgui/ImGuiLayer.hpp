#ifndef _IMGUI_LAYER_HPP_
#define _IMGUI_LAYER_HPP_

#include "navia/core/Layer.hpp"
#include "navia/events/MouseEvent.hpp"
#include "navia/events/KeyEvent.hpp"
#include "navia/events/WindowEvent.hpp"

namespace Navia {
class ImGuiLayer : public Layer {
public:
    ImGuiLayer();

    void setBlockEvents(bool blockEvents);

    void setDarkThemeColors();

    void onAttach() override;
    void onDetach() override;
    void onEvent(Event& event) override;

    void begin();
    void end();

private:
    bool blockEvents = true;
};
}

#endif