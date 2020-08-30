#include "navia/core/Input.hpp"
#include "navia/core/KeyCodes.hpp"
#include "navia/core/OrthographicCameraController.hpp"

namespace Navia {
OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
    : aspectRatio(aspectRatio), rotation(rotation),
      camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel) {}

float OrthographicCameraController::getZoomLevel() const {
    return zoomLevel;
}

void OrthographicCameraController::setZoomLevel(float zoomLevel) {
    this->zoomLevel = zoomLevel;
}

OrthographicCamera& OrthographicCameraController::getCamera() {
    return camera;
}

const OrthographicCamera& OrthographicCameraController::getCamera() const {
    return camera;
}

void OrthographicCameraController::onUpdate(Timestep timestep) {
    NAVIA_PROFILE_FUNCTION();

    if (Input::isKeyPressed(Key::A)) {
        cameraPosition.x -= std::cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * timestep;
        cameraPosition.y -= std::sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * timestep;
    }
    else if (Input::isKeyPressed(Key::D)) {
        cameraPosition.x += std::cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * timestep;
        cameraPosition.y += std::sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * timestep;
    }
    if (Input::isKeyPressed(Key::W)) {
        cameraPosition.x += -std::sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * timestep;
        cameraPosition.y += std::cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * timestep;
    }
    else if (Input::isKeyPressed(Key::S)) {
        cameraPosition.x -= -std::sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * timestep;
        cameraPosition.y -= std::cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * timestep;
    }
    camera.setPosition(cameraPosition);
    cameraTranslationSpeed = zoomLevel;

    if (rotation) {
        if (Input::isKeyPressed(Key::Q)) {
            cameraRotation += cameraRotationSpeed * timestep;
        } else if (Input::isKeyPressed(Key::E)) {
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

void OrthographicCameraController::onResize(float width, float height) {
    aspectRatio = width / height;
    camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
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

    onResize(static_cast<float>(event.getWidth()), static_cast<float>(event.getHeight()));
    return false;
}
}