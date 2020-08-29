#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include "navia/core/Base.hpp"
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
    static Ref<Shader> create(const std::string& filepath);
    static Ref<Shader> create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
    virtual ~Shader() = default;

    virtual std::string getName() const = 0;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setInt(const std::string& name, int value) = 0;
    virtual void setIntArray(const std::string& name, int* array, size_t count) = 0;

    virtual void setFloat(const std::string& name, float value) = 0;
    virtual void setFloat2(const std::string& name, const glm::vec2& vector) = 0;
    virtual void setFloat3(const std::string& name, const glm::vec3& vector) = 0;
    virtual void setFloat4(const std::string& name, const glm::vec4& vector) = 0;

    virtual void setMat3(const std::string& name, const glm::mat3& matrix) = 0;
    virtual void setMat4(const std::string& name, const glm::mat4& matrix) = 0;
};
}

#endif