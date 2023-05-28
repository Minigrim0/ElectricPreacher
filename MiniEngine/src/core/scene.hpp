#pragma once

#include <string>
#include <SDL.h>

#include "core/screen.hpp"
#include "core/core.hpp"

#include "event/layer_manager.hpp"
#include "event/interactible.hpp"


/**
 * @brief A window is a part of the UI that can be drawn and updated
 * Windows can be generated from a JSON file
 */
namespace MiniEngine {
    class ME_API Scene : public Event::Interactible {
        public:
            Scene();
            Scene(std::string name);
            virtual ~Scene();

            //Getters
            bool is_current() const;
            std::string get_name() const;

            //Setters
            void set_running(bool);
            int set_font(std::string path);

            //Others
            void add_layer(uint8_t index, Event::Layer* layer);
            void add_interactible(uint8_t layer_index, Event::Interactible* interactible);

            void OnUpdate(int time_elapsed);
            bool OnEvent(SDL_Event* event);
            void OnRender(Screen* sc);

        private:
            bool m_current; //! Should be shown and updated ?
            std::string m_name; //! Name to identify the scene

            Event::LayerManager* m_layer_manager;
    };
}
