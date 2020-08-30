#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "navia/core/Base.hpp"

namespace Navia {
class Texture {
public:
    virtual ~Texture() = default;

    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;
    virtual uint32_t getRendererId() const = 0;
    virtual void setData(void* data, uint32_t size) = 0;

    virtual void bind(uint32_t slot = 0) const = 0;

    virtual bool operator==(const Texture& rhs) const = 0;
};

class Texture2D : public Texture {
public:
    static Ref<Texture2D> create(uint32_t width, uint32_t height);
    static Ref<Texture2D> create(const std::string& filepath);
};
}

#endif