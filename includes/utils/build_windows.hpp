#pragma once

#include <map>

#include "screen/screen.hpp"
#include "UI/window.hpp"

/**
 * @brief Build all windows from a JSON file
 * 
 * @param screen The screen to draw on
 * @param windows The map of windows to fill
 */
void build_windows(Screen *screen, std::map<std::string, Window> *windows);
