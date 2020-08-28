#include "navia/platform/opengl/OpenGLIndexBuffer.hpp"
#include <glad/glad.h>

namespace Navia {
OpenGLIndexBuffer::OpenGLIndexBuffer(size_t* indices, size_t count) : count(count) {
    NAVIA_PROFILE_FUNCTION();

    glCreateBuffers(1, &rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(size_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    NAVIA_PROFILE_FUNCTION();

    glDeleteBuffers(1, &rendererId);
}

size_t OpenGLIndexBuffer::getCount() const {
    return count;
}

void OpenGLIndexBuffer::bind() const {
    NAVIA_PROFILE_FUNCTION();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
}

void OpenGLIndexBuffer::unbind() const {
    NAVIA_PROFILE_FUNCTION();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}