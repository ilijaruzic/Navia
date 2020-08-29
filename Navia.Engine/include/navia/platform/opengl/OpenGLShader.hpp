#ifndef _OPENGL_SHADER_HPP_
#define _OPENGL_SHADER_HPP_

#include <string>
#include "navia/core/Base.hpp"
#include "navia/renderer/Shader.hpp"

typedef unsigned int GLenum;

namespace Navia {
class OpenGLShader : public Shader {
public:
    OpenGLShader(const std::string& filepath);
    OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
    ~OpenGLShader();

    std::string getName() const override;

    void bind() const override;
    void unbind() const override;

    void setInt(const std::string& name, int value) override;
    void setIntArray(const std::string& name, int* array, size_t count) override;

    void setFloat(const std::string& name, float value) override;
    void setFloat2(const std::string& name, const glm::vec2& vector) override;
    void setFloat3(const std::string& name, const glm::vec3& vector) override;
    void setFloat4(const std::string& name, const glm::vec4& vector) override;

    void setMat3(const std::string& name, const glm::mat3& matrix) override;
    void setMat4(const std::string& name, const glm::mat4& matrix) override;

private:
    size_t rendererId{ 0 };
    std::string name;

    std::string getSourceFromFile(const std::string& filepath) const;
    std::unordered_map<GLenum, std::string> preprocess(const std::string& source) const;
    void compileAndLink(const std::unordered_map<GLenum, std::string>& sources);

    void uploadUniformInt(const std::string& name, int value);
    void uploadUniformIntArray(const std::string& name, int* array, size_t count);

    void uploadUniformFloat(const std::string& name, float value);
    void uploadUniformFloat2(const std::string& name, const glm::vec2& vector);
    void uploadUniformFloat3(const std::string& name, const glm::vec3& vector);
    void uploadUniformFloat4(const std::string& name, const glm::vec4& vector);

    void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
    void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);
};
}

#endif