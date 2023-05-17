#pragma once

#include <map>

#include "core/screen.hpp"
#include "UI/window.hpp"

/**
 * @brief Build all windows from a JSON file
 * 
 * @param windows The map of windows to fill
 */
namespace MiniEngine {
    namespace Utils {
        void build_windows(std::map<std::string, UI::Window> *windows, Screen* screen);
    }
}