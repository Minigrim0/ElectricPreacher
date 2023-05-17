#pragma once

#include <map>

#include <core/screen.hpp>
#include <UI/window.hpp>

#include "constants.hpp"

/**
 * @brief Build all windows from a JSON file
 * 
 * @param windows The map of windows to fill
 */
void build_windows(std::map<std::string, UI::Window> *windows);
