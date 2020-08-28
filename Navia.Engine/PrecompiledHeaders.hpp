#ifndef _PRECOMPILED_HEADERS_HPP_
#define _PRECOMPILED_HEADERS_HPP_

#include <cctype>
#include <cstdint>
#include <cstddef>
#include <type_traits>

#include <algorithm>
#include <functional>
#include <memory>
#include <utility>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <array>
#include <initializer_list>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

#include "navia/core/Logger.hpp"
#include "navia/debug/Instrumentor.hpp"

#ifdef NAVIA_PLATFORM_WINDOWS
    #include <Windows.h>
#endif

#endif