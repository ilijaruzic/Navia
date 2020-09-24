#ifndef _SCENE_CAMERA_HPP_
#define _SCENE_CAMERA_HPP_

#include "navia/renderer/Camera.hpp"

namespace Navia {
class SceneCamera : public Camera {
public:
    enum class ProjectionType {
        Perspective = 0,
        Orthographic = 1
    };

    SceneCamera();

    ProjectionType getProjectionType() const;
    void setProjectionType(ProjectionType type);

    float getPerspectiveVerticalFOV() const;
    void setPerspectiveVerticalFOV(float fov);
    float getPerspectiveNearClip() const;
    void setPerspectiveNearClip(float nearClip);
    float getPerspectiveFarClip() const;
    void setPerspectiveFarClip(float farClip);
    void setPerspective(float fov, float nearClip, float farClip);

    float getOrthographicSize() const;
    void setOrthographicSize(float size);
    float getOrthographicNearClip() const;
    void setOrthographicNearClip(float nearClip);
    float getOrthographicFarClip() const;
    void setOrthographicFarClip(float farClip);
    void setOrthographic(float size, float nearClip, float farClip);

    void setViewportSize(uint32_t width, uint32_t height);

private:
    ProjectionType projectionType = ProjectionType::Orthographic;
    float perspectiveVerticalFOV = glm::radians(45.0f);
    float perspectiveNearClip = 0.0001f;
    float perspectiveFarClip = 1000.0f;
    float orthographicSize = 10.0f;
    float orthographicNearClip = -1.0f;
    float orthographicFarClip = 1.0f;
    float aspectRatio = 0.0f;

    void recalculateProjection();
};
}

#endif