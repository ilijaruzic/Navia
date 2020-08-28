#include "navia/core/Input.hpp"
#include "navia/core/KeyCodes.hpp"
#include "navia/core/OrthographicCameraController.hpp"

namespace Navia {
OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : aspectRatio(aspectRatio), rotation(rotation), camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel) {}

float OrthographicCameraController::getZoomLevel() const {
    return zoomLevel;
}

void OrthographicCameraController::setZoomLevel(float zoomLevel) {
    OrthographicCameraController::zoomLevel = zoomLevel;
}

OrthographicCamera& OrthographicCameraController::getCamera() {
    return camera;
}

const OrthographicCamera& OrthographicCameraController::getCamera() const {
    return const_cast<OrthographicCameraController&>(*this).getCamera();
}

void OrthographicCameraController::onUpdate(Timestep timestep) {
    NAVIA_PROFILE_FUNCTION();

    if (Input::isKeyPressed(NAVIA_KEY_A)) {
        cameraPosition.x -= cameraTranslationSpeed * timestep;
    }
    else if (Input::isKeyPressed(NAVIA_KEY_D)) {
        cameraPosition.x += cameraTranslationSpeed * timestep;
    }
    if (Input::isKeyPressed(NAVIA_KEY_S)) {
        cameraPosition.y -= cameraTranslationSpeed * timestep;
    }
    else if (Input::isKeyPressed(NAVIA_KEY_W)) {
        cameraPosition.y += cameraTranslationSpeed * timestep;
    }
    camera.setPosition(cameraPosition);
    cameraTranslationSpeed = zoomLevel;

    if (rotation) {
        if (Input::isKeyPressed(NAVIA_KEY_Q)) {
            cameraRotation += cameraRotationSpeed * timestep;
        } else if (Input::isKeyPressed(NAVIA_KEY_E)) {
            cameraRotation -= cameraRotationSpeed * timestep;
        }
        camera.setRotation(cameraRotation);
    }

}

void OrthographicCameraController::onEvent(Event& event) {
    NAVIA_PROFILE_FUNCTION();

    EventDispatcher dispatcher{ event };
    dispatcher.dispatch<MouseScrolledEvent>(NAVIA_BIND_EVENT_CALLBACK(OrthographicCameraController::onMouseScrolled));
    dispatcher.dispatch<WindowResizeEvent>(NAVIA_BIND_EVENT_CALLBACK(OrthographicCameraController::onWindowResize));
}

bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& event) {
    NAVIA_PROFILE_FUNCTION();

    zoomLevel -= event.getYOffset() * 0.25f;
    zoomLevel = std::max(zoomLevel, 0.25f);
    camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    return false;
}

bool OrthographicCameraController::onWindowResize(WindowResizeEvent& event) {
    NAVIA_PROFILE_FUNCTION();

    aspectRatio = static_cast<float>(event.getWidth()) / static_cast<float>(event.getHeight());
    camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    return false;
}
}