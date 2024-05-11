#pragma once

#include <vector>

#include "core/screen.hpp"

#include "UI/widgets/button.hpp"
#include "UI/widgets/text_input.hpp"

#include "event/interactible.hpp"

namespace MiniEngine {
namespace UI {
/**
 * @author Minigrim0
 * @brief A console is a widget that can be used to display text to the player
 * It contains a text input that can be used to either send a message to a server,
 * or to enter a command
 */
class Console : public Event::Interactible {
  public:
    // Constructors
    Console();
    Console(int, int);
    Console(int, int, int);
    Console(int, int, int, int);
    explicit Console(TTF_Font *);
    ~Console();

    Console &operator=(const Console &) = delete;

    // Getters

    // Setters
    void set_position(int, int);
    void set_size(int, int);
    int set_font(TTF_Font *);
    int set_font(std::string, int);

    // Interactible
    bool OnEvent(SDL_Event *e) override;
    void OnRender(Screen *sc) override;
    void OnUpdate(int te) override;

    // Others
    void init(Screen *);

  private:
    int update_layout();
    void init_send_button();
    void OnSendButtonPressed();
    void OnTextSubmit(std::string);

    SDL_Rect m_rect;
    std::vector<Widgets::Button *> m_history; // The previous inputs and outputs
    TTF_Font *m_font;
    SDL_Texture *m_background_texture;

    Widgets::TextInput *m_input;
    Widgets::Button *m_send_button;

    int m_nb_visible_lines;
    int m_line_height;

    Uint8 m_alpha;

    bool m_visible;
};
} // namespace UI
} // namespace MiniEngine
