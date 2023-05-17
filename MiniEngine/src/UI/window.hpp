#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <nlohmann/json.hpp>

#include "UI/widgets/button.hpp"
#include "core/screen.hpp"

/**
 * @brief A window is a part of the UI that can be drawn and updated
 * Windows can be generated from a JSON file
 */
namespace MiniEngine {
    namespace UI {
        class Window{
            public:
                Window();
                virtual ~Window();

                //Getters
                bool is_running() const;
                std::string get_title() const;

                //Setters
                void set_running(bool);
                void set_title(nlohmann::json title);
                int set_font(std::string path);

                //Others
                void add_button(Widgets::Button* newButton);
                int add_buttons(nlohmann::json buttons);
                void update(SDL_Event* event, Screen* screen, std::string *current_window, std::string *action);
                void draw(Screen* sc);
                int createfrom(std::string JSONsource);

            private:
                bool m_window_running; //! Should be shown and updated ?
                std::string m_window_name; //! Name to identify the window

                std::vector<Widgets::Button*> m_buttons; //! Buttons on the window
                Widgets::Button* m_title; //! Title of the window
        };
    }
}