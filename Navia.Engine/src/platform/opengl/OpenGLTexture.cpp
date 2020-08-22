#include "navia/platform/opengl/OpenGLTexture.hpp"
#include <glad/glad.h>
#include <stb_image.h>

namespace Navia {
OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath) : filepath(filepath) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    NAVIA_CORE_ASSERT(data, "Failed to load image!");
    this->width = width;
    this->height = height;

    auto internalFormat{ 0 };
    auto format{ 0 };
    if (channels == 4) {
        internalFormat = GL_RGBA8;
        format = GL_RGBA;
    }
    else if (channels == 3) {
        internalFormat = GL_RGB8;
        format = GL_RGB;
    }
    NAVIA_CORE_ASSERT(internalFormat & format, "Unsuported format!");

    glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
    glTextureStorage2D(rendererId, 1, internalFormat, this->width, this->height);

    glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(rendererId, 0, 0, 0, this->width, this->height, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D() {
    glDeleteTextures(1, &rendererId);
}

size_t OpenGLTexture2D::getWidth() const {
    return width;
}

size_t OpenGLTexture2D::getHeight() const {
    return height;
}

void OpenGLTexture2D::bind(size_t slot) const {
    glBindTextureUnit(slot, rendererId);
}
}