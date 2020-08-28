#ifndef _OPENGL_TEXTURE_HPP_
#define _OPENGL_TEXTURE_HPP_

#include <cstddef>
#include "navia/renderer/Texture.hpp"

namespace Navia {
class OpenGLTexture2D : public Texture2D {
public:
    OpenGLTexture2D(size_t width, size_t height);
    OpenGLTexture2D(const std::string& filepath);
    ~OpenGLTexture2D();

    size_t getWidth() const override;
    size_t getHeight() const override;
    void setData(void* data, size_t size) override;

    void bind(size_t slot) const override;

    bool operator==(const Texture& rhs) const override;

private:
    std::string filepath;
    size_t width{ 0 };
    size_t height{ 0 };
    size_t internalFormat;
    size_t format;
    size_t rendererId{ 0 };
};
}

#endif