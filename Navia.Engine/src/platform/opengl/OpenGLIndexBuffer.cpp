#include "navia/platform/opengl/OpenGLIndexBuffer.hpp"
#include <glad/glad.h>

namespace Navia {
OpenGLIndexBuffer::OpenGLIndexBuffer(size_t* indices, size_t count) : count(count) {
    glCreateBuffers(1, &rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(size_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    glDeleteBuffers(1, &rendererId);
}

size_t OpenGLIndexBuffer::getCount() const {
    return count;
}

void OpenGLIndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
}

void OpenGLIndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}