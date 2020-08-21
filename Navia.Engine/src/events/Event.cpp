#include "Event.hpp"

namespace Navia {
int operator&(const EventCategory& lhs, const EventCategory& rhs) {
    return static_cast<int>(lhs) & static_cast<int>(rhs);
}
int operator|(const EventCategory& lhs, const EventCategory& rhs) {
    return static_cast<int>(lhs) | static_cast<int>(rhs);
}

bool Event::isCategory(EventCategory category) {
    return getCategoryFlags() & static_cast<int>(category);
}

std::ostream& operator<<(std::ostream& ostream, const Event& rhs) {
    return ostream << rhs.toString();
}
}