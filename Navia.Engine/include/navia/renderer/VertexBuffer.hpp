#ifndef _VERTEX_BUFFER_HPP_
#define _VERTEX_BUFFER_HPP_

#include "navia/core/Base.hpp"
#include "navia/renderer/BufferLayout.hpp"

namespace Navia {
class VertexBuffer {
public:
    static Ref<VertexBuffer> create(uint32_t size);
    static Ref<VertexBuffer> create(float* vertices, uint32_t size);
    virtual ~VertexBuffer() = default;

    virtual const BufferLayout& getLayout() const = 0;
    virtual void setLayout(const BufferLayout& layout) = 0;
    virtual void setData(const void* data, uint32_t size) = 0;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
};
}

#endif