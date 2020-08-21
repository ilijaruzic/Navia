#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Navia {
class Logger {
public:
    static void init();

    static std::shared_ptr<spdlog::logger>& getCoreLogger();
    static std::shared_ptr<spdlog::logger>& getClientLogger();

private:
    static std::shared_ptr<spdlog::logger> coreLogger;
    static std::shared_ptr<spdlog::logger> clientLogger;
};
}

#define NAVIA_CORE_TRACE(...)   ::Navia::Logger::getCoreLogger()->trace(__VA_ARGS__)
#define NAVIA_CORE_INFO(...)    ::Navia::Logger::getCoreLogger()->info(__VA_ARGS__)
#define NAVIA_CORE_WARN(...)    ::Navia::Logger::getCoreLogger()->warn(__VA_ARGS__)
#define NAVIA_CORE_ERROR(...)   ::Navia::Logger::getCoreLogger()->error(__VA_ARGS__)
#define NAVIA_CORE_FATAL(...)   ::Navia::Logger::getCoreLogger()->fatal(__VA_ARGS__)

#define NAVIA_TRACE(...)        ::Navia::Logger::getClientLogger()->trace(__VA_ARGS__)
#define NAVIA_INFO(...)         ::Navia::Logger::getClientLogger()->info(__VA_ARGS__)
#define NAVIA_WARN(...)         ::Navia::Logger::getClientLogger()->warn(__VA_ARGS__)
#define NAVIA_ERROR(...)        ::Navia::Logger::getClientLogger()->error(__VA_ARGS__)
#define NAVIA_FATAL(...)        ::Navia::Logger::getClientLogger()->fatal(__VA_ARGS__)

#endif