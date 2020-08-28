#ifndef _CORE_HPP_
#define _CORE_HPP_

#ifdef NAVIA_DEBUG
    #define NAVIA_ENABLE_ASSERTS
    #define NAVIA_ENABLE_PROFILE
#endif

#ifdef NAVIA_ENABLE_ASSERTS
    #define NAVIA_CORE_ASSERT(x, ...) { if(!(x)) { NAVIA_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define NAVIA_ASSERT(x, ...) { if(!(x)) { NAVIA_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define NAVIA_CORE_ASSERT(x, ...)
	#define NAVIA_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define NAVIA_BIND_EVENT_CALLBACK(callback) std::bind(&callback, this, std::placeholders::_1)

namespace Navia {
template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T, typename ... Args>
constexpr Scope<T> createScope(Args&& ... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename ... Args>
constexpr Ref<T> createRef(Args&& ... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}
}

#endif