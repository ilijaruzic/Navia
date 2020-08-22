#ifndef _VERTEX_ARRAY_HPP_
#define _VERTEX_ARRAY_HPP_

#include "navia/core/Core.hpp"
#include "navia/renderer/IndexBuffer.hpp"
#include "navia/renderer/VertexBuffer.hpp"

namespace Navia {
class VertexArray {
public:
    static Ref<VertexArray> create();
    virtual ~VertexArray() = default;

    virtual void setIndexBuffer(Ref<IndexBuffer> indexBuffer) = 0;
    virtual void addVertexBuffer(Ref<VertexBuffer> vertexBuffer) = 0;

    virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;
    virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
};
}

#endif