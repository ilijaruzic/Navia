#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include "navia/core/Core.hpp"
#include <glm/glm.hpp>

namespace Navia {
enum class ShaderDatatype {
    None = 0,
    Bool,
    Int, Int2, Int3, Int4,
    Float, Float2, Float3, Float4,
    Mat3, Mat4
};

class Shader {
public:
    static Shader* create(const std::string& vertexSource, const std::string& fragmentSource);
    virtual ~Shader() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
};
}

#endif