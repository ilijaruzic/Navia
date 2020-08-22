#ifndef _SHADER_LIBRARY_HPP_
#define _SHADER_LIBRARY_HPP_

#include "navia/core/Core.hpp"
#include "navia/renderer/Shader.hpp"

namespace Navia {
class ShaderLibrary {
public:
    void add(Ref<Shader> shader);
    void add(const std::string& name, Ref<Shader> shader);
    Ref<Shader> load(const std::string& filepath);
    Ref<Shader> load(const std::string& name, const std::string& filepath);

    bool contains(const std::string& name) const;
    Ref<Shader> get(const std::string& name);

private:
    std::unordered_map<std::string, Ref<Shader>> shaders;
};
}

#endif