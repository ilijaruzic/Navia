#include "navia/renderer/BufferLayout.hpp"

namespace Navia {
static size_t getShaderDatatypeSize(ShaderDatatype type) {
    switch (type) {
        case ShaderDatatype::None:
            return 0;
        case ShaderDatatype::Bool:
            return 1;
        case ShaderDatatype::Int:
        case ShaderDatatype::Float:
            return 4;
        case ShaderDatatype::Int2:
        case ShaderDatatype::Float2:
            return 4 * 2;
        case ShaderDatatype::Int3:
        case ShaderDatatype::Float3:
            return 4 * 3;
        case ShaderDatatype::Int4:
        case ShaderDatatype::Float4:
            return 4 * 4;
        case ShaderDatatype::Mat3:
            return 4 * 3 * 3;
        case ShaderDatatype::Mat4:
            return 4 * 4 * 4;
    }
    NAVIA_CORE_ASSERT(false, "Unknown shader datatype!");
    return 0;
}

BufferElement::BufferElement(ShaderDatatype type, const std::string& name, bool normalized) : name(name), type(type), size(getShaderDatatypeSize(type)), normalized(normalized) {}

size_t BufferElement::getComponentCount() const {
    switch (type) {
        case ShaderDatatype::None:
            return 0;
        case ShaderDatatype::Bool:
        case ShaderDatatype::Int:
        case ShaderDatatype::Float:
            return 1;
        case ShaderDatatype::Int2:
        case ShaderDatatype::Float2:
            return 2;
        case ShaderDatatype::Int3:
        case ShaderDatatype::Float3:
            return 3;
        case ShaderDatatype::Int4:
        case ShaderDatatype::Float4:
            return 4;
        case ShaderDatatype::Mat3:
            return 3 * 3;
        case ShaderDatatype::Mat4:
            return 4 * 4;
    }
    NAVIA_CORE_ASSERT(false, "Unknown shader datatype!");
    return 0;
}

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) : elements(elements) {
    calculateOffsetAndStride();
}

const std::vector<BufferElement>& BufferLayout::getElements() const {
    return elements;
}

size_t BufferLayout::getStride() const {
    return stride;
}

std::vector<BufferElement>::iterator BufferLayout::begin() {
    return elements.begin();
}

std::vector<BufferElement>::iterator BufferLayout::end() {
    return elements.end();
}

std::vector<BufferElement>::reverse_iterator BufferLayout::rbegin() {
    return elements.rbegin();
}

std::vector<BufferElement>::reverse_iterator BufferLayout::rend() {
    return elements.rend();
}

std::vector<BufferElement>::const_iterator BufferLayout::begin() const {
    return elements.begin();
}

std::vector<BufferElement>::const_iterator BufferLayout::end() const {
    return elements.end();
}

std::vector<BufferElement>::const_reverse_iterator BufferLayout::rbegin() const {
    return elements.rbegin();
}

std::vector<BufferElement>::const_reverse_iterator BufferLayout::rend() const {
    return elements.rend();
}

void BufferLayout::calculateOffsetAndStride() {
    size_t offset{ 0 };
    stride = 0;
    for (auto& element : elements) {
        element.offset = offset;
        offset += element.size;
        stride += element.size;
    }
}
}