#pragma once

#include <vector>

#include "core/screen.hpp"

#include "UI/widgets/button.hpp"
#include "UI/widgets/text_input.hpp"

#include "event/interactible.hpp"

/**
 * @author Minigrim0
 * @brief A console is a widget that can be used to display text to the player
 * It contains a text input that can be used to either send a message to a server,
 * or to enter a command
 */
namespace MiniEngine {
    namespace UI {
        class Console : public Event::Interactible {
        public:
            // Constructors
            Console();
            Console(int, int);
            Console(int, int, int);
            Console(int, int, int, int);
            explicit Console(TTF_Font *);
            ~Console();

            Console &operator=(const Console &);

            // Getters

            // Setters
            void set_position(int, int);
            void set_size(int, int);
            int set_font(TTF_Font *);
            int set_font(std::string, int);

            // Interactible
            bool OnEvent(SDL_Event*) override;
            int OnRender(Screen *) override;
            int OnUpdate(int time_elapsed) override;

            // Others
            void init(Screen *);
            int update_layout(Screen *);
            void init_send_button();
            void create_entry(Screen *);

        private:
            SDL_Rect m_rect;
            std::vector<Widgets::Button *> m_history; // The previous inputs and outputs
            TTF_Font *m_font;
            SDL_Texture *m_background_texture;

            Widgets::TextInput *m_input;
            Widgets::Button *m_send_button;

            int m_nb_visible_lines;
            int m_line_height;

            Uint8 m_alpha;
        };
    }
}
