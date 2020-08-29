#include "navia/platform/opengl/OpenGLVertexArray.hpp"
#include <glad/glad.h>

namespace Navia {
static GLenum convertShaderDatatypeToOpenGLBasetype(ShaderDatatype type) {
    switch (type) {
        case ShaderDatatype::None:
            return GL_NONE;
        case ShaderDatatype::Bool:
            return GL_BOOL;
        case ShaderDatatype::Int:
        case ShaderDatatype::Int2:
        case ShaderDatatype::Int3:
        case ShaderDatatype::Int4:
            return GL_INT;
        case ShaderDatatype::Float:
        case ShaderDatatype::Float2:
        case ShaderDatatype::Float3:
        case ShaderDatatype::Float4:
        case ShaderDatatype::Mat3:
        case ShaderDatatype::Mat4:
            return GL_FLOAT;
    }
    NAVIA_CORE_ASSERT(false, "Unknown shader datatype!");
    return GL_NONE;
}

OpenGLVertexArray::OpenGLVertexArray() {
    NAVIA_PROFILE_FUNCTION();

    glCreateVertexArrays(1, &rendererId);
}

OpenGLVertexArray::~OpenGLVertexArray() {
    NAVIA_PROFILE_FUNCTION();

    glDeleteVertexArrays(1, &rendererId);
}

void Navia::OpenGLVertexArray::setIndexBuffer(Ref<IndexBuffer> indexBuffer) {
    NAVIA_PROFILE_FUNCTION();

    glBindVertexArray(rendererId);
    indexBuffer->bind();
    this->indexBuffer = indexBuffer;
}

void Navia::OpenGLVertexArray::addVertexBuffer(Ref<VertexBuffer> vertexBuffer) {
    NAVIA_PROFILE_FUNCTION();

    NAVIA_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex buffer has no layout!");
    glBindVertexArray(rendererId);
    vertexBuffer->bind();

    const auto& layout = vertexBuffer->getLayout();
    for (const auto& element : layout) {
        switch (element.type) {
            case ShaderDatatype::Float:
            case ShaderDatatype::Float2:
            case ShaderDatatype::Float3:
            case ShaderDatatype::Float4:
            case ShaderDatatype::Int:
            case ShaderDatatype::Int2:
            case ShaderDatatype::Int3:
            case ShaderDatatype::Int4:
            case ShaderDatatype::Bool:
            {
                glEnableVertexAttribArray(vertexBufferIndex);
                glVertexAttribPointer(vertexBufferIndex,
                                      element.getComponentCount(),
                                      convertShaderDatatypeToOpenGLBasetype(element.type),
                                      element.normalized ? GL_TRUE : GL_FALSE,
                                      layout.getStride(),
                                      (const void*)element.offset);
                vertexBufferIndex++;
                break;
            }
            case ShaderDatatype::Mat3:
            case ShaderDatatype::Mat4:
            {
                size_t count = element.getComponentCount();
                for (size_t i = 0; i < count; ++i)
                {
                    glEnableVertexAttribArray(vertexBufferIndex);
                    glVertexAttribPointer(vertexBufferIndex,
                                          count,
                                          convertShaderDatatypeToOpenGLBasetype(element.type),
                                          element.normalized ? GL_TRUE : GL_FALSE,
                                          layout.getStride(),
                                          (const void*)(element.offset + sizeof(float) * count * i));
                    glVertexAttribDivisor(vertexBufferIndex, 1);
                    vertexBufferIndex++;
                }
                break;
            }
            default:
                NAVIA_CORE_ASSERT(false, "Unknown ShaderDatatype!");
        }
    }

    vertexBuffers.push_back(vertexBuffer);
}

const Ref<IndexBuffer>& OpenGLVertexArray::getIndexBuffer() const {
    return indexBuffer;
}

const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::getVertexBuffers() const {
    return vertexBuffers;
}

void Navia::OpenGLVertexArray::bind() const {
    NAVIA_PROFILE_FUNCTION();

    glBindVertexArray(rendererId);
}

void Navia::OpenGLVertexArray::unbind() const {
    NAVIA_PROFILE_FUNCTION();

    glBindVertexArray(0);
}
}