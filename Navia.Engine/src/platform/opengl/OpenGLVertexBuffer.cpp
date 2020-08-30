#include "navia/platform/opengl/OpenGLVertexBuffer.hpp"
#include <glad/glad.h>

namespace Navia {
OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
    NAVIA_PROFILE_FUNCTION();

    glCreateBuffers(1, &rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
    NAVIA_PROFILE_FUNCTION();

    glCreateBuffers(1, &rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    NAVIA_PROFILE_FUNCTION();

    glDeleteBuffers(1, &rendererId);
}

const BufferLayout& OpenGLVertexBuffer::getLayout() const {
    return layout;
}

void OpenGLVertexBuffer::setLayout(const BufferLayout& layout) {
    this->layout = layout;
}

void OpenGLVertexBuffer::setData(const void* data, uint32_t size) {
    NAVIA_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void OpenGLVertexBuffer::bind() const {
    NAVIA_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
}

void OpenGLVertexBuffer::unbind() const {
    NAVIA_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}