#ifndef _INSTRUMENTOR_HPP_
#define _INSTRUMENTOR_HPP_

#include "navia/core/Core.hpp"

namespace Navia {
struct ProfileResult {
    std::string name;
    size_t start;
    size_t end;
    size_t threadId;
};

struct InstrumentorSession {
    std::string name;
};

class Instrumentor {
public:
    static Instrumentor& getInstance();

    void beginSession(const std::string& name, const std::string& filepath = "results.json");
    void endSession();

private:
    InstrumentorSession* currentSession{ nullptr };
    std::ofstream stream;
    size_t profileCount{ 0 };

    friend class InstrumentationTimer;
    Instrumentor() = default;

    void writeHeader();
    void writeProfile(const ProfileResult& result);
    void writeFooter();
};

class InstrumentationTimer {
public:
    InstrumentationTimer(const char* name);
    ~InstrumentationTimer();

private:
    const char* name;
    std::chrono::time_point<std::chrono::steady_clock> startTimePoint;
    bool stopped{ false };

    void stop();
};
}

#ifdef NAVIA_ENABLE_PROFILE
    #define NAVIA_PROFILE_BEGIN_SESSION(name, filepath) ::Navia::Instrumentor::getInstance().beginSession(name, filepath)
    #define NAVIA_PROFILE_END_SESSION() ::Navia::Instrumentor::getInstance().endSession()
    #define NAVIA_PROFILE_SCOPE(name) ::Navia::InstrumentationTimer timer##__LINE__(name);
    #define NAVIA_PROFILE_FUNCTION() NAVIA_PROFILE_SCOPE(__FUNCSIG__)
#else
    #define NAVIA_PROFILE_BEGIN_SESSION(name, filepath)
    #define NAVIA_PROFILE_END_SESSION()
    #define NAVIA_PROFILE_SCOPE(name)
    #define NAVIA_PROFILE_FUNCTION()
#endif

#endif