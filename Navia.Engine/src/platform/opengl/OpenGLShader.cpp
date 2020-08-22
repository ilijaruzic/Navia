#include "navia/platform/opengl/OpenGLShader.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Navia {
OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* source = static_cast<const GLchar*>(vertexSource.c_str());
    glShaderSource(vertexShader, 1, &source, 0);
    glCompileShader(vertexShader);
    GLint isCompiled{};
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
        GLint maxLength{};
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        glDeleteShader(vertexShader);
        NAVIA_CORE_ERROR("{0}", infoLog.data());
        NAVIA_CORE_ASSERT(false, "Vertex shader failed to compile!");
        return;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    source = static_cast<const GLchar*>(fragmentSource.c_str());
    glShaderSource(fragmentShader, 1, &source, 0);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength{};
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
        NAVIA_CORE_ERROR("{0}", infoLog.data());
        NAVIA_CORE_ASSERT(false, "Fragment shader failed to compile!");
        return;
    }

    rendererId = glCreateProgram();
    glAttachShader(rendererId, vertexShader);
    glAttachShader(rendererId, fragmentShader);
    glLinkProgram(rendererId);
    GLint isLinked{};
    glGetProgramiv(rendererId, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength{};
        glGetProgramiv(rendererId, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(rendererId, maxLength, &maxLength, &infoLog[0]);
        glDeleteProgram(rendererId);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        NAVIA_CORE_ERROR("{0}", infoLog.data());
        NAVIA_CORE_ASSERT(false, "Shader failed to link!");
        return;
    }
    glDetachShader(rendererId, vertexShader);
    glDetachShader(rendererId, fragmentShader);
}

OpenGLShader::~OpenGLShader() {
    glDeleteProgram(rendererId);
}

void OpenGLShader::bind() const {
    glUseProgram(rendererId);
}

void OpenGLShader::unbind() const {
    glUseProgram(0);
}

void OpenGLShader::uploadUniformInt(const std::string& name, int value) {
    auto location = glGetUniformLocation(rendererId, name.c_str());
    glUniform1i(location, value);
}

void OpenGLShader::uploadUniformFloat(const std::string& name, float value) {
    auto location = glGetUniformLocation(rendererId, name.c_str());
    glUniform1f(location, value);
}

void OpenGLShader::uploadUniformFloat2(const std::string& name, const glm::vec2& vector) {
    auto location = glGetUniformLocation(rendererId, name.c_str());
    glUniform2f(location, vector.x, vector.y);
}

void OpenGLShader::uploadUniformFloat3(const std::string& name, const glm::vec3& vector) {
    auto location = glGetUniformLocation(rendererId, name.c_str());
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void OpenGLShader::uploadUniformFloat4(const std::string& name, const glm::vec4& vector) {
    auto location = glGetUniformLocation(rendererId, name.c_str());
    glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void OpenGLShader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
    auto location = glGetUniformLocation(rendererId, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
    auto location = glGetUniformLocation(rendererId, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
}