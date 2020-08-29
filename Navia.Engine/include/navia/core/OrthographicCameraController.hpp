#ifndef _ORTHOGRAPHIC_CAMERA_CONTROLLER_HPP_
#define _ORTHOGRAPHIC_CAMERA_CONTROLLER_HPP_

#include "navia/core/Base.hpp"
#include "navia/core/Timestep.hpp"
#include "navia/events/Event.hpp"
#include "navia/events/MouseEvent.hpp"
#include "navia/events/WindowEvent.hpp"
#include "navia/renderer/OrthographicCamera.hpp"
#include <glm/glm.hpp>

namespace Navia {
class OrthographicCameraController {
public:
    OrthographicCameraController(float aspectRatio, bool rotation = false);

    float getZoomLevel() const;
    void setZoomLevel(float zoomLevel);
    OrthographicCamera& getCamera();
    const OrthographicCamera& getCamera() const;

    void onUpdate(Timestep timestep);
    void onEvent(Event& event);
    void onResize(float width, float height);

private:
    float aspectRatio;
    float zoomLevel{ 1.0f };
    OrthographicCamera camera;

    glm::vec3 cameraPosition{ 0.0f };
    float cameraTranslationSpeed{ 5.0f };
    float cameraRotation{ 0.0f };
    float cameraRotationSpeed{ 180.0f };
    bool rotation;

    bool onMouseScrolled(MouseScrolledEvent& event);
    bool onWindowResize(WindowResizeEvent& event);
};
}

#endif