#include "navia/platform/opengl/OpenGLShader.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Navia {
static GLenum getShaderTypeFromString(const std::string& type) {
    if (type == "vertex") {
        return GL_VERTEX_SHADER;
    }
    if (type == "fragment" || type == "pixel") {
        return GL_FRAGMENT_SHADER;
    }
    NAVIA_CORE_ASSERT(false, "Unknown shader type!");
    return 0;
}

OpenGLShader::OpenGLShader(const std::string& filepath) {
    NAVIA_PROFILE_FUNCTION();

    auto source = getSourceFromFile(filepath);
    auto sources = preprocess(source);
    compileAndLink(sources);
    auto lastSlash = filepath.find_last_of("/\\");
    lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
    auto lastDot = filepath.rfind('.');
    auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
    name = filepath.substr(lastSlash, count);
}

OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) : name(name) {
    NAVIA_PROFILE_FUNCTION();

    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = vertexSource;
    sources[GL_FRAGMENT_SHADER] = fragmentSource;
    compileAndLink(sources);
}

OpenGLShader::~OpenGLShader() {
    NAVIA_PROFILE_FUNCTION();

    glDeleteProgram(rendererId);
}

std::string OpenGLShader::getName() const {
    return name;
}

void OpenGLShader::bind() const {
    NAVIA_PROFILE_FUNCTION();

    glUseProgram(rendererId);
}

void OpenGLShader::unbind() const {
    NAVIA_PROFILE_FUNCTION();

    glUseProgram(0);
}

void OpenGLShader::setInt(const std::string& name, int value) {
    NAVIA_PROFILE_FUNCTION();

    uploadUniformInt(name, value);
}

void OpenGLShader::setFloat(const std::string& name, float value) {
    NAVIA_PROFILE_FUNCTION();

    uploadUniformFloat(name, value);
}

void OpenGLShader::setFloat2(const std::string& name, const glm::vec2& vector) {
    NAVIA_PROFILE_FUNCTION();

    uploadUniformFloat2(name, vector);
}

void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& vector) {
    NAVIA_PROFILE_FUNCTION();

    uploadUniformFloat3(name, vector);
}

void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& vector) {
    NAVIA_PROFILE_FUNCTION();

    uploadUniformFloat4(name, vector);
}

void OpenGLShader::setMat3(const std::string& name, const glm::mat3& matrix) {
    NAVIA_PROFILE_FUNCTION();

    uploadUniformMat3(name, matrix);
}

void OpenGLShader::setMat4(const std::string& name, const glm::mat4& matrix) {
    NAVIA_PROFILE_FUNCTION();

    uploadUniformMat4(name, matrix);
}

std::string OpenGLShader::getSourceFromFile(const std::string& filepath) const {
    NAVIA_PROFILE_FUNCTION();

    std::string data;
    if (std::ifstream file(filepath, std::ios::in | std::ios::binary); file.is_open()) {
        file.seekg(0, std::ios::end);
        data.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&data[0], data.size());
        file.close();
    }
    else {
        NAVIA_CORE_ERROR("Failed to open file: {0}!", filepath);
    }
    return data;
}

std::unordered_map<GLenum, std::string> OpenGLShader::preprocess(const std::string& source) const {
    NAVIA_PROFILE_FUNCTION();

    std::unordered_map<GLenum, std::string> sources;
    const char* typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t position = source.find(typeToken, 0);
    while (position != std::string::npos) {
        size_t end = source.find_first_of("\r\n", position);
        NAVIA_CORE_ASSERT(end != std::string::npos, "Syntax error!");
        size_t begin = position + typeTokenLength + 1;
        std::string type = source.substr(begin, end - begin);
        NAVIA_CORE_ASSERT(getShaderTypeFromString(type), "Invalid shader type specifier!");
        size_t next = source.find_first_not_of("\r\n", end);
        NAVIA_CORE_ASSERT(next != std::string::npos, "Syntax error!");
        position = source.find(typeToken, next);
        sources[getShaderTypeFromString(type)] = (position == std::string::npos) ? source.substr(next) : source.substr(next, position - next);
    }
    return sources;
}


void OpenGLShader::compileAndLink(const std::unordered_map<GLenum, std::string>& sources) {
    NAVIA_PROFILE_FUNCTION();

    auto programId = glCreateProgram();
    std::array<GLenum, 2> shaderIds;
    size_t index{ 0 };
    for (const auto& [shaderType, shaderSource] : sources) {
        GLuint shader = glCreateShader(shaderType);
        const GLchar* source = static_cast<const GLchar*>(shaderSource.c_str());
        glShaderSource(shader, 1, &source, 0);
        glCompileShader(shader);
        GLint isCompiled{ 0 };
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength{ 0 };
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
            glDeleteShader(shader);
            NAVIA_CORE_ERROR("{0}", infoLog.data());
            NAVIA_CORE_ASSERT(false, "Shader failed to compile!");
            return;
        }
        glAttachShader(programId, shader);
        shaderIds[index++] = shader;
    }
    glLinkProgram(programId);
    GLint isLinked{ 0 };
    glGetProgramiv(programId, GL_LINK_STATUS, (int*) &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength{ 0 };
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);
        glDeleteProgram(programId);
        for (auto shaderId : shaderIds) {
            glDeleteShader(shaderId);
        }
        NAVIA_CORE_ERROR("{0}", infoLog.data());
        NAVIA_CORE_ASSERT(false, "Shader failed to link!");
        return;
    }
    for (auto shaderId : shaderIds) {
        glDetachShader(programId, shaderId);
    }
    rendererId = programId;
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