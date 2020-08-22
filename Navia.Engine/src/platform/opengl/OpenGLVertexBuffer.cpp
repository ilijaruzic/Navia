#include "navia/platform/opengl/OpenGLVertexBuffer.hpp"
#include <glad/glad.h>

namespace Navia {
OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, size_t size) {
    glCreateBuffers(1, &rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    glDeleteBuffers(1, &rendererId);
}

const BufferLayout& OpenGLVertexBuffer::getLayout() const {
    return layout;
}

void OpenGLVertexBuffer::setLayout(const BufferLayout& layout) {
    this->layout = layout;
}

void OpenGLVertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, rendererId);
}

void OpenGLVertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}