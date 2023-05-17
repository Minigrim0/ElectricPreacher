#pragma once

#include <vector>

#include "core/screen.hpp"

#include "UI/widgets/button.hpp"
#include "UI/widgets/text_input.hpp"
#include "UI/widgets/widgets.hpp"

/**
 * @author Minigrim0
 * @brief A console is a widget that can be used to display text to the player
 * It contains a text input that can be used to either send a message to a server,
 * or to enter a command
 */
namespace MiniEngine {
namespace UI {
class Console : public Widgets::Widget
{
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

    // Others
    void init(Core::Screen *);
    int draw(Core::Screen *) override;
    int update(SDL_Event *, Core::Screen*) override;
    int update_layout(Core::Screen *);
    void init_send_button();
    void create_entry(Core::Screen *);

private:
    SDL_Rect m_rect;
    std::vector<Widgets::Button*> m_history; // The previous inputs and outputs
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