#include "navia/debug/Instrumentor.hpp"

namespace Navia {
Instrumentor& Instrumentor::getInstance() {
    static Instrumentor instance;
    return instance;
}

void Instrumentor::beginSession(const std::string& name, const std::string& filepath) {
    stream.open(filepath);
    writeHeader();
    currentSession = new InstrumentorSession{ name };
}

void Instrumentor::endSession() {
    writeFooter();
    stream.close();
    delete currentSession;
    currentSession = nullptr;
    profileCount = 0;
}

void Instrumentor::writeHeader() {
    stream << "{\"otherData\": {},\"traceEvents\":[";
    stream.flush();
}

void Instrumentor::writeProfile(const ProfileResult& result) {
    if (profileCount++ > 0) {
        stream << ",";
    }
    std::string name = result.name;
    std::replace(name.begin(), name.end(), '"', '\'');
    stream << "{";
    stream << "\"cat\":\"function\",";
    stream << "\"dur\":" << (result.end - result.start) << ',';
    stream << "\"name\":\"" << name << "\",";
    stream << "\"ph\":\"X\",";
    stream << "\"pid\":0,";
    stream << "\"tid\":" << result.threadId << ",";
    stream << "\"ts\":" << result.start;
    stream << "}";
    stream.flush();
}

void Instrumentor::writeFooter() {
    stream << "]}";
    stream.flush();
}

InstrumentationTimer::InstrumentationTimer(const char* name) : name(name), startTimePoint(std::chrono::high_resolution_clock::now()) {}

InstrumentationTimer::~InstrumentationTimer() {
    if (!stopped) {
        stop();
    }
}

void InstrumentationTimer::stop() {
    auto endTimePoint = std::chrono::high_resolution_clock::now();
    size_t start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
    size_t end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
    size_t threadId = std::hash<std::thread::id>{}(std::this_thread::get_id());
    Instrumentor::getInstance().writeProfile(ProfileResult{ name, start, end, threadId });
    stopped = true;
}
}