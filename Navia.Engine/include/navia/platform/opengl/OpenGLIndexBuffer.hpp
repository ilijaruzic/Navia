#ifndef _OPENGL_INDEX_BUFFER_HPP_
#define _OPENGL_INDEX_BUFFER_HPP_

#include "navia/renderer/IndexBuffer.hpp"

namespace Navia {
class OpenGLIndexBuffer : public IndexBuffer {
public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    ~OpenGLIndexBuffer();

    uint32_t getCount() const override;

    void bind() const override;
    void unbind() const override;

private:
    uint32_t rendererId = 0;
    uint32_t count;
};
}

#endif