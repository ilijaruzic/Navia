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
    size_t getColorAttachment() const override;

    void bind() override;
    void unbind() override;

    void resize(size_t width, size_t height) override;
    void invalidate();

private:
    size_t rendererId{ 0 };
    size_t colorAttachment{ 0 };
    size_t depthAttachment{ 0 };
    FramebufferProperties properties;
};
}

#endif