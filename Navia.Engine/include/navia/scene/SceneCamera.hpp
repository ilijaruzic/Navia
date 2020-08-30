#ifndef _SCENE_CAMERA_HPP_
#define _SCENE_CAMERA_HPP_

#include "navia/renderer/Camera.hpp"

namespace Navia {
class SceneCamera : public Camera {
public:
    SceneCamera();

    float getOrthographicSize() const;
    void setOrthographicSize(float size);
    void setOrthographic(float size, float nearClip, float farClip);
    void setViewportSize(uint32_t width, uint32_t height);

private:
    float orthographicSize = 10.0f;
    float orthographicNearClip = -1.0f;
    float orthographicFarClip = 1.0f;
    float aspectRatio = 0.0f;

    void recalculateProjection();
};
}

#endif