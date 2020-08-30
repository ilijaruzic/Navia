#ifndef _BUFFERLAYOUT_HPP_
#define _BUFFERLAYOUT_HPP_

#include "navia/renderer/Shader.hpp"

namespace Navia {
struct BufferElement {
    std::string name;
    ShaderDatatype type;
    uint32_t size;
    uint32_t offset{ 0 };
    bool normalized;

    BufferElement() = default;
    BufferElement(ShaderDatatype type, const std::string& name, bool normalized = false);

    uint32_t getComponentCount() const;
};

class BufferLayout {
public:
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<BufferElement>& elements);

    const std::vector<BufferElement>& getElements() const;

    uint32_t getStride() const;

    std::vector<BufferElement>::iterator begin();
    std::vector<BufferElement>::iterator end();
    std::vector<BufferElement>::reverse_iterator rbegin();
    std::vector<BufferElement>::reverse_iterator rend();
    std::vector<BufferElement>::const_iterator begin() const;
    std::vector<BufferElement>::const_iterator end() const;
    std::vector<BufferElement>::const_reverse_iterator rbegin() const;
    std::vector<BufferElement>::const_reverse_iterator rend() const;

private:
    std::vector<BufferElement> elements;
    uint32_t stride{ 0 };

    void calculateOffsetAndStride();
};
}

#endif