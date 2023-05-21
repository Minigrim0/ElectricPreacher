#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <nlohmann/json.hpp>

#include "core/screen.hpp"
#include "core/core.hpp"

#include "UI/widgets/button.hpp"
#include "event/interactible.hpp"

/**
 * @brief A window is a part of the UI that can be drawn and updated
 * Windows can be generated from a JSON file
 */
namespace MiniEngine {
    class ME_API Scene : public Event::Interactible {
        public:
            Scene();
            virtual ~Scene();

            //Getters
            bool is_current() const;
            std::string get_name() const;

            //Setters
            void set_running(bool);
            void set_title(nlohmann::json title, Screen* screen);
            int set_font(std::string path);

            //Others
            void add_button(UI::Widgets::Button* newButton);
            int add_buttons(nlohmann::json buttons, Screen* screen);

            void OnUpdate(int time_elapsed);
            bool OnEvent(SDL_Event* event);
            void OnRender(Screen* sc);

            int createfrom(std::string JSONsource, Screen* screen);

        private:
            bool m_current; //! Should be shown and updated ?
            std::string m_name; //! Name to identify the scene

            std::vector<UI::Widgets::Button*> m_buttons; //! Buttons on the scene
            UI::Widgets::Button* m_title; //! Title of the scene
    };
}
