#pragma once

#include <functional>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "core/screen.hpp"
#include "event/interactible.hpp"

namespace MiniEngine {
namespace UI {
namespace Widgets {
/**
 * @brief A text input is a widget that can be used to get text input from the player
 */
class TextInput : public Event::Interactible {
  public:
    TextInput();
    ~TextInput();

    TextInput &operator=(const TextInput &) = delete;

    // Getters
    std::string get_text() const;
    bool collide(SDL_Event *) const;
    bool collide(int, int) const;
    TTF_Font *get_font() const;
    bool is_empty() const;

    // Setters
    void set_position(int, int);
    void set_text_size(int, int);
    void set_font(std::string, int);
    void set_font(TTF_Font *);

    void set_OnSubmit(std::function<void(std::string)>);

    // Implementations
    void OnRender(Screen *sc) override;
    void OnUpdate(int time_elapsed) override;
    bool OnEvent(SDL_Event *e) override;

    void update_image();
    void flush();

  private:
    bool handle_mouse_up(SDL_Event *e);
    bool handle_key_down(SDL_Event *e);

    SDL_Texture *m_tex;
    SDL_Texture *m_cursor;
    SDL_Surface *m_background_image;
    SDL_Rect m_rect;
    TTF_Font *m_font;

    std::string m_current_input;
    Sint32 m_cursor_pos;
    Sint32 m_selection_len;

    std::function<void(std::string)> m_OnSubmit;

    bool m_is_active;
};

} // namespace Widgets
} // namespace UI
} // namespace MiniEngine
