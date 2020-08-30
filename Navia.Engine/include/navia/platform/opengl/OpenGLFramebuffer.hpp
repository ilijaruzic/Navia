#ifndef _OPENGLFRAMEBUFFER_HPP_
#define _OPENGLFRAMEBUFFER_HPP_

#include <glm/fwd.hpp>
#include "navia/renderer/Framebuffer.hpp"

namespace Navia {
class OpenGLFramebuffer : public Framebuffer {
public:
    OpenGLFramebuffer(const FramebufferProperties& properties);
    ~OpenGLFramebuffer();

    const FramebufferProperties& getProperties() const override;
    uint32_t getColorAttachment() const override;

    void bind() override;
    void unbind() override;

    void resize(uint32_t width, uint32_t height) override;
    void invalidate();

private:
    uint32_t rendererId = 0;
    uint32_t colorAttachment = 0;
    uint32_t depthAttachment = 0;
    FramebufferProperties properties;
};
}

#endif