#ifndef _GRAPHICS_CONTEXT_HPP_
#define _GRAPHICS_CONTEXT_HPP_

namespace Navia {
class GraphicsContext {
public:
    virtual ~GraphicsContext() = default;

    virtual void init() = 0;
    virtual void swapBuffers() = 0;
};
}

#endif