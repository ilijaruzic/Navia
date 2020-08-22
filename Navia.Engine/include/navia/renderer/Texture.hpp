#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "navia/core/Core.hpp"

namespace Navia {
class Texture {
public:
    virtual ~Texture() = default;

    virtual size_t getWidth() const = 0;
    virtual size_t getHeight() const = 0;

    virtual void bind(size_t slot = 0) const = 0;
};

class Texture2D : public Texture {
public:
    static Ref<Texture2D> create(const std::string& filepath);
};
}

#endif