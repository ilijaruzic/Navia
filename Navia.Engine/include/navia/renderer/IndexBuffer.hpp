#ifndef _INDEX_BUFFER_HPP_
#define _INDEX_BUFFER_HPP_

#include "navia/core/Base.hpp"

namespace Navia {
class IndexBuffer {
public:
    static Ref<IndexBuffer> create(uint32_t* indices, uint32_t count);
    virtual ~IndexBuffer() = default;

    virtual uint32_t getCount() const = 0;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
};
}

#endif