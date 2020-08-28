#include "navia/platform/opengl/OpenGLTexture.hpp"
#include <glad/glad.h>
#include <stb_image.h>

namespace Navia {
OpenGLTexture2D::OpenGLTexture2D(size_t width, size_t height) : width(width), height(height), internalFormat(GL_RGBA8), format(GL_RGBA) {
    NAVIA_PROFILE_FUNCTION();

    glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
    glTextureStorage2D(rendererId, 1, internalFormat, width, height);

    glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath) : filepath(filepath) {
    NAVIA_PROFILE_FUNCTION();

    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data{ nullptr };
    {
        NAVIA_PROFILE_SCOPE("Navia::OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath) — stbi_load");

        data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    }
    NAVIA_CORE_ASSERT(data, "Failed to load image!");
    this->width = width;
    this->height = height;

    GLenum internalFormat{ 0 };
    GLenum format{ 0 };
    if (channels == 4) {
        internalFormat = GL_RGBA8;
        format = GL_RGBA;
    }
    else if (channels == 3) {
        internalFormat = GL_RGB8;
        format = GL_RGB;
    }
    this->internalFormat = internalFormat;
    this->format = format;
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
    NAVIA_PROFILE_FUNCTION();

    glDeleteTextures(1, &rendererId);
}

size_t OpenGLTexture2D::getWidth() const {
    return width;
}

size_t OpenGLTexture2D::getHeight() const {
    return height;
}

void OpenGLTexture2D::setData(void* data, size_t size) {
    NAVIA_PROFILE_FUNCTION();

    size_t bytesPerPixel = format == GL_RGBA ? 4 : 3;
    NAVIA_CORE_ASSERT(size == width * height * bytesPerPixel, "Data have to be entire texture!");
    glTextureSubImage2D(rendererId, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture2D::bind(size_t slot) const {
    NAVIA_PROFILE_FUNCTION();

    glBindTextureUnit(slot, rendererId);
}

bool OpenGLTexture2D::operator==(const Texture& rhs) const {
    return rendererId == static_cast<const OpenGLTexture2D&>(rhs).rendererId;
}
}