#ifndef _FRAMEBUFFER_HPP_
#define _FRAMEBUFFER_HPP_

#include "navia/core/Base.hpp"

namespace Navia {
struct FramebufferProperties {
    uint32_t width;
    uint32_t height;
    uint32_t samples{ 1 };

    bool swapChainTarget{ false };

};

class Framebuffer {
public:
    static Ref<Framebuffer> create(const FramebufferProperties& properties);
    virtual ~Framebuffer() = default;

    virtual const FramebufferProperties& getProperties() const = 0;
    virtual uint32_t getColorAttachment() const = 0;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual void resize(uint32_t width, uint32_t height) = 0;
};
}

#endif