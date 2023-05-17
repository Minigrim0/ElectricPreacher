#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <nlohmann/json.hpp>

#include "core/screen.hpp"
#include "core/core.hpp"

#include "UI/widgets/button.hpp"

/**
 * @brief A window is a part of the UI that can be drawn and updated
 * Windows can be generated from a JSON file
 */
namespace MiniEngine {
    namespace UI {
        class ME_API Window{
            public:
                Window();
                virtual ~Window();

                //Getters
                bool is_running() const;
                std::string get_title() const;

                //Setters
                void set_running(bool);
                void set_title(nlohmann::json title, Screen* screen);
                int set_font(std::string path);

                //Others
                void add_button(Widgets::Button* newButton);
                int add_buttons(nlohmann::json buttons, Screen* screen);
                void update(SDL_Event* event, Screen* screen, std::string *current_window, std::string *action);
                void draw(Screen* sc);
                int createfrom(std::string JSONsource, Screen* screen);

            private:
                bool m_window_running; //! Should be shown and updated ?
                std::string m_window_name; //! Name to identify the window

                std::vector<Widgets::Button*> m_buttons; //! Buttons on the window
                Widgets::Button* m_title; //! Title of the window
        };
    }
}