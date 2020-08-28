#include "navia/platform/opengl/OpenGLVertexBuffer.hpp"
#include <glad/glad.h>

namespace Navia {
OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, size_t size) {
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

void OpenGLVertexBuffer::bind() const {
    NAVIA_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
}

void OpenGLVertexBuffer::unbind() const {
    NAVIA_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}