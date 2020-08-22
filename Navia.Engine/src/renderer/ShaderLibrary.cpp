#include "navia/renderer/ShaderLibrary.hpp"

namespace Navia {
void ShaderLibrary::add(Ref<Shader> shader) {
    add(shader->getName(), shader);
}

void ShaderLibrary::add(const std::string& name, Ref<Shader> shader) {
    NAVIA_CORE_ASSERT(!contains(name), "Shader already exists!");
    shaders[name] = shader;
}

Ref<Shader> ShaderLibrary::load(const std::string& filepath) {
    auto shader = Shader::create(filepath);
    add(shader);
    return shader;
}

Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath) {
    auto shader = Shader::create(filepath);
    add(name, shader);
    return shader;
}

bool ShaderLibrary::contains(const std::string& name) const {
    return shaders.find(name) != shaders.end();
}

Ref<Shader> ShaderLibrary::get(const std::string& name) {
    NAVIA_CORE_ASSERT(contains(name), "Shader does not exist!");
    return shaders[name];
}
}