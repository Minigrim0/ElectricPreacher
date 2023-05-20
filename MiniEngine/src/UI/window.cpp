#include <SDL_events.h>
#include <SDL_mouse.h>
#include <fstream>
#include <SDL.h>

#include <nlohmann/json.hpp>

#include "UI/window.hpp"
#include "UI/widgets/button.hpp"
#include "core/log.hpp"
#include "core/screen.hpp"

namespace MiniEngine {
    namespace UI {
        Window::Window() {}

        Window::~Window() {}

        /**
         * @brief Get the running state of the window
         *
         * @return true The window is currently running
         * @return false The window is not running
         */
        bool Window::is_running() const {
            return m_window_running;
        }

        /**
         * @brief Get the title of the window
         *
         * @return std::string The title of the window
         */
        std::string Window::get_title() const {
            return m_window_name;
        }

        /**
         * @brief Set the running state of the window
         *
         * @param running Whether the window should be running or not
         */
        void Window::set_running(bool running) {
            m_window_running = running;
        }

        /**
         * @brief Create a button that holds the title
         *
         * @param title The json description of the title
         */
        void Window::set_title(nlohmann::json title, Screen* screen) {
            int off_x = title["offset"][0];
            int off_y = title["offset"][1];

            m_title = new Widgets::Button;
            m_title->set_text(title["text"]);
            m_title->set_position(0, 0);

            m_title->set_size(screen->get_width(), screen->get_height());

            m_title->set_text_color(
                title["text-color"]["r"],
                title["text-color"]["g"],
                title["text-color"]["b"]
            );
            m_title->set_background_color(0, 0, 0, 0);
            if (title["text_position_type"] == "txt")
                m_title->set_text_pos(
                    title["text-position"]
                );
            else
                m_title->set_text_pos(
                    title["text-position_x"],
                    title["text-position_y"]
                );

            m_title->set_text_offset(off_x, off_y);
            m_title->update_layout(screen->get_font(title["font_id"]));
        }

        /**
         * @brief Add an already created button to the list of buttons
         *
         * @param newButton The button to add
         */
        void Window::add_button(Widgets::Button* newButton) {
            m_buttons.push_back(newButton);
        }

        /**
         * @brief Add a collection of button from a parsed json list
         *
         * @param buttons The list of buttons to add
         * @return int 0 on success, -1 on error
         */
        int Window::add_buttons(nlohmann::json buttons, Screen* screen) {
            for (unsigned int index = 0; index < buttons.size(); ++index) {
                m_buttons.push_back(new Widgets::Button);

                m_buttons.back()->set_text(buttons[index]["name"]);

                m_buttons.back()->set_position(
                    buttons[index]["position_x"],
                    buttons[index]["position_y"]
                );

                m_buttons.back()->set_size(
                    buttons[index]["size_x"],
                    buttons[index]["size_y"]
                );

                m_buttons.back()->set_text_color(
                    buttons[index]["text-color"]["r"],
                    buttons[index]["text-color"]["g"],
                    buttons[index]["text-color"]["b"]
                );

                m_buttons.back()->set_background_color(
                    buttons[index]["background-color"]["r"],
                    buttons[index]["background-color"]["g"],
                    buttons[index]["background-color"]["b"]
                );

                m_buttons.back()->set_contour_color(
                    buttons[index]["contour-color"]["r"],
                    buttons[index]["contour-color"]["g"],
                    buttons[index]["contour-color"]["b"]
                );

                // Set text-position, via text or absolute coordinates
                if (buttons[index]["text_position_type"] == "txt") {
                    m_buttons.back()->set_text_pos(
                        buttons[index]["text-position"]
                    );
                }
                else {
                    m_buttons.back()->set_text_pos(
                        buttons[index]["text-position_x"],
                        buttons[index]["text-position_y"]
                    );
                }

                m_buttons.back()->set_action_type(buttons[index]["action_type"], buttons[index]["action_operand"]);

                //Finally update the button image
                m_buttons.back()->update_layout(screen->get_font(buttons[index]["font_id"]));
            }
            return 0;
        }

        /**
         * @brief Updates the window, handles events
         *
         * @param event The event handler, used to get current event if any
         * @param screen The screen on which to draw and from which to get informations
         * @param current_window A pointer to the current window name, used to switch windows
         * @param action A pointer to the current action, used to switch windows or quit the game
         */
        void Window::update(SDL_Event* event, Screen* screen, std::string* current_window, std::string* action) {
            for (unsigned i = 0; i < m_buttons.size(); i++) {
                m_buttons[i]->OnEvent(event);
                if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (m_buttons[i]->collide(mouseX, mouseY)) {
                        *action = m_buttons[i]->get_action_type();
                        if (*action == "switch_window") {
                            *current_window = m_buttons[i]->get_action_operand();
                        }
                        else if (*action == "quit_game") {
                            ME_CORE_WARN("Need to handle quit_game action");
                        }
                    }
                }
            }
        }

        /**
         * @brief Draws the window to the screen
         *
         * @param sc The screen on which to draw
         */
        void Window::draw(Screen* sc) {
            for (unsigned i = 0; i < m_buttons.size(); i++) {
                m_buttons[i]->OnRender(sc);
            }
            m_title->OnRender(sc);
        }

        /**
         * @brief Create a window from a JSON file
         *
         * @param screen The screen on which to draw
         * @param JSONsource The path to the JSON file
         * @return 0 on success, -1 on error
         */
        int Window::createfrom(std::string JSONsource, Screen* screen) {
            std::ifstream json_in(JSONsource.c_str());
            nlohmann::json root;
            json_in >> root;

            // Setup window-wide informations
            m_window_name = root["window_name"];
            screen->add_font(root["font_path"], root["font_size"], root["font_id"]);

            // Setup Buttons
            const nlohmann::json buttons = root["Buttons"];
            this->add_buttons(buttons, screen);

            // Setup title
            const nlohmann::json title = root["Title"];
            this->set_title(title, screen);

            json_in.close();
            return 0;
        }
    }
}
