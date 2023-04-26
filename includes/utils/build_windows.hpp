#pragma once

#include <map>

#include "screen/screen.hpp"
#include "UI/window.hpp"

void build_windows(Screen *screen, std::map<std::string, Window> *windows);
