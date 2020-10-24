#ifndef _PLATFORM_UTILS_HPP_
#define _PLATFORM_UTILS_HPP_

namespace Navia {
class FileDialog {
public:
    static std::string openFile(const char* filter);
    static std::string saveFile(const char* filter);
};
}

#endif