#ifndef _OPENGL_SHADER_HPP_
#define _OPENGL_SHADER_HPP_

#include <string>
#include "navia/core/Core.hpp"
#include "navia/renderer/Shader.hpp"

namespace Navia {
class OpenGLShader : public Shader {
public:
    OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
    ~OpenGLShader();

    void bind() const override;
    void unbind() const override;

    void uploadUniformInt(const std::string& name, int value);

    void uploadUniformFloat(const std::string& name, float value);
    void uploadUniformFloat2(const std::string& name, const glm::vec2& vector);
    void uploadUniformFloat3(const std::string& name, const glm::vec3& vector);
    void uploadUniformFloat4(const std::string& name, const glm::vec4& vector);

    void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
    void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
    size_t rendererId{ 0 };
};
}

#endif