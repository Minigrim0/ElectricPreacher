#pragma once

#include <map>

#include "screen/screen.hpp"
#include "UI/window.hpp"

/**
 * @brief Build all windows from a JSON file
 * 
 * @param windows The map of windows to fill
 */
void build_windows(std::map<std::string, Window> *windows);
