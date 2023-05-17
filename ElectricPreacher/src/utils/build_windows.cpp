#include "utils/build_windows.hpp"

#include <map>
#include <filesystem>

void build_windows(std::map<std::string, UI::Window> *windows){
    std::string UI_path = std::filesystem::current_path().string() + "/assets/UI/";
    const std::filesystem::path pathToShow{ UI_path };

    for (const auto& entry : std::filesystem::directory_iterator(pathToShow)) {
        const auto filenameStr = entry.path().filename().string();
        if(entry.is_regular_file()){
            UI::Window tmp_window;
            tmp_window.createfrom(UI_path + static_cast<std::string>(filenameStr));

            (*windows)[tmp_window.get_title()] = tmp_window;
        }
    }
}
