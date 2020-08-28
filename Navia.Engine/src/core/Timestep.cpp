#include "navia/core/Timestep.hpp"

namespace Navia {
Timestep::Timestep(float time) : time(time) {}

float Timestep::getSeconds() const {
    return time;
}

float Timestep::getMilliseconds() const {
    return time * 1000.f;
}

Timestep::operator float() const {
    return time;
}
}