#ifndef _OPENGL_VERTEX_BUFFER_HPP_
#define _OPENGL_VERTEX_BUFFER_HPP_

#include "navia/renderer/VertexBuffer.hpp"

namespace Navia {
class OpenGLVertexBuffer : public VertexBuffer {
public:
    OpenGLVertexBuffer(size_t size);
    OpenGLVertexBuffer(float* vertices, size_t size);
    ~OpenGLVertexBuffer();

    const BufferLayout& getLayout() const override;
    void setLayout(const BufferLayout& layout) override;
    void setData(const void* data, size_t size) override;

    void bind() const override;
    void unbind() const override;

private:
    size_t rendererId{ 0 };
    BufferLayout layout;
};
}

#endif