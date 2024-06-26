#pragma once

#include <SDL.h>
#include <string>

#include "core/screen.hpp"
#include "event/interactible.hpp"

namespace MiniEngine {
namespace UI {
namespace Widgets {
/**
 * @author Minigrim0
 * @brief A notification is a widget that displays a message to the player
 * It is given a lifetime in milliseconds, and will disappear after that time
 * It can contain a text, an icon, and a progress bar
 */
class Notification : public Event::Interactible {
  public:
    // Constructors
    Notification();
    ~Notification();

    // Operator
    Notification &operator=(const Notification &) = delete;

    // Setters
    void set_position(int, int);
    void set_text(std::string);
    void set_icon(SDL_Texture *);
    void set_lifetime(Uint16);
    void set_offset(int offset);

    void set_width(int);

    // Getters
    int get_height() const;

    bool is_alive() const;

    // Others
    bool OnEvent(SDL_Event *event) override;
    void OnRender(Screen *sc) override;
    void OnUpdate(int time_elapsed) override;

    void init(Screen *, std::string font);

  private:
    std::string m_content;

    SDL_Rect m_position;
    int m_offset;

    SDL_Color m_progress_bar_color;
    SDL_Color m_text_color;

    SDL_Texture *m_background;
    SDL_Texture *m_text_texture;
    SDL_Texture *m_progress_bar;
    SDL_Texture *m_icon;

    Uint16 m_total_lifetime;   // Max 65536 ms
    Uint16 m_current_lifetime; // Max 65536 ms

    Uint8 m_alpha;
};

} // namespace Widgets
} // namespace UI
} // namespace MiniEngine
