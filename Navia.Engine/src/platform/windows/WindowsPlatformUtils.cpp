#include "navia/core/Application.hpp"
#include "navia/utils/PlatformUtils.hpp"
#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Navia {
std::string FileDialog::openFile(const char* filter) {
    OPENFILENAMEA dialog;
    CHAR buffer[256];
    std::memset(buffer, 0, sizeof(buffer));
    ZeroMemory(&dialog, sizeof(OPENFILENAME));
    dialog.lStructSize = sizeof(OPENFILENAME);
    dialog.hwndOwner = glfwGetWin32Window(static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow()));
    dialog.lpstrFile = buffer;
    dialog.nMaxFile = sizeof(buffer);
    dialog.lpstrFilter = filter;
    dialog.nFilterIndex = 1;
    dialog.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
    if (GetOpenFileNameA(&dialog) == TRUE) {
        return dialog.lpstrFile;
    }
    return std::string{};
}

std::string FileDialog::saveFile(const char* filter) {
    OPENFILENAMEA dialog;
    CHAR buffer[256];
    std::memset(buffer, 0, sizeof(buffer));
    ZeroMemory(&dialog, sizeof(OPENFILENAME));
    dialog.lStructSize = sizeof(OPENFILENAME);
    dialog.hwndOwner = glfwGetWin32Window(static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow()));
    dialog.lpstrFile = buffer;
    dialog.nMaxFile = sizeof(buffer);
    dialog.lpstrFilter = filter;
    dialog.nFilterIndex = 1;
    dialog.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
    if (GetSaveFileNameA(&dialog) == TRUE) {
        return dialog.lpstrFile;
    }
    return std::string{};
}
}
