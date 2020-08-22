#ifndef _OPENGL_INDEX_BUFFER_HPP_
#define _OPENGL_INDEX_BUFFER_HPP_

#include "navia/renderer/IndexBuffer.hpp"

namespace Navia {
class OpenGLIndexBuffer : public IndexBuffer {
public:
    OpenGLIndexBuffer(size_t* indices, size_t count);
    ~OpenGLIndexBuffer();

    size_t getCount() const override;

    void bind() const override;
    void unbind() const override;

private:
    size_t rendererId{ 0 };
    size_t count;
};
}

#endif