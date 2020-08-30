#include "navia/platform/opengl/OpenGLFramebuffer.hpp"
#include <glad/glad.h>

namespace Navia {
static constexpr uint32_t MaxFramebufferSize = 8192;

OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferProperties& properties) : properties(properties) {
    invalidate();
}

OpenGLFramebuffer::~OpenGLFramebuffer() {
    glDeleteFramebuffers(1, &rendererId);
    glDeleteTextures(1, &colorAttachment);
    glDeleteTextures(1, &depthAttachment);
}

const FramebufferProperties& OpenGLFramebuffer::getProperties() const {
    return properties;
}

uint32_t OpenGLFramebuffer::getColorAttachment() const {
    return colorAttachment;
}

void OpenGLFramebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, rendererId);
    glViewport(0, 0, properties.width, properties.height);
}

void OpenGLFramebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::resize(uint32_t width, uint32_t height) {
    if (width == 0 || height == 0 || width > MaxFramebufferSize || height > MaxFramebufferSize) {
        NAVIA_CORE_WARN("Attempt to resize framebuffer to {0}x{1} failed!", width, height);
        return;
    }
    properties.width = width;
    properties.height = height;
    invalidate();
}

void OpenGLFramebuffer::invalidate() {
    if (rendererId) {
        glDeleteFramebuffers(1, &rendererId);
        glDeleteTextures(1, &colorAttachment);
        glDeleteTextures(1, &depthAttachment);
    }

    glCreateFramebuffers(1, &rendererId);
    glBindFramebuffer(GL_FRAMEBUFFER, rendererId);

    glCreateTextures(GL_TEXTURE_2D, 1, &colorAttachment);
    glBindTexture(GL_TEXTURE_2D, colorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, properties.width, properties.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachment);
    glBindTexture(GL_TEXTURE_2D, depthAttachment);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, properties.width, properties.height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachment, 0);

    NAVIA_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
}