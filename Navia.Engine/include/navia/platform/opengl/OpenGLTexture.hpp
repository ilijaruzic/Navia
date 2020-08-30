#ifndef _OPENGL_TEXTURE_HPP_
#define _OPENGL_TEXTURE_HPP_

#include <cstddef>
#include "navia/renderer/Texture.hpp"

namespace Navia {
class OpenGLTexture2D : public Texture2D {
public:
    OpenGLTexture2D(uint32_t width, uint32_t height);
    OpenGLTexture2D(const std::string& filepath);
    ~OpenGLTexture2D();

    uint32_t getWidth() const override;
    uint32_t getHeight() const override;
    uint32_t getRendererId() const override;

    void setData(void* data, uint32_t size) override;

    void bind(uint32_t slot) const override;

    bool operator==(const Texture& rhs) const override;

private:
    uint32_t rendererId = 0;
    std::string filepath;
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t internalFormat;
    uint32_t format;
};
}

#endif