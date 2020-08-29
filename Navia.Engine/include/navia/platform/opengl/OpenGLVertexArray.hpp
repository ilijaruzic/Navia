#ifndef _OPENGL_VERTEX_ARRAY_HPP_
#define _OPENGL_VERTEX_ARRAY_HPP_

#include <memory>
#include <vector>
#include "navia/core/Base.hpp"
#include "navia/renderer/VertexArray.hpp"

namespace Navia {
class OpenGLVertexArray : public VertexArray {
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray();

    void setIndexBuffer(Ref<IndexBuffer> indexBuffer) override;
    void addVertexBuffer(Ref<VertexBuffer> vertexBuffer) override;

    const Ref<IndexBuffer>& getIndexBuffer() const override;
    const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override;

    void bind() const override;
    void unbind() const override;

private:
    size_t rendererId{ 0 };
    size_t vertexBufferIndex{ 0 };
    Ref<IndexBuffer> indexBuffer;
    std::vector<Ref<VertexBuffer>> vertexBuffers;
};
}

#endif