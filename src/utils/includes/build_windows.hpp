#ifndef build_windows_hpp
    #define build_windows_hpp

#include <map>

#include "../src/screen/includes/screen.hpp"
#include "../src/UI/includes/window.hpp"

void build_windows(Screen *screen, std::map<std::string, Window> *windows);

#endif