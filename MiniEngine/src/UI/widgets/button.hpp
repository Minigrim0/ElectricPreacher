#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <functional>

#include "core/core.hpp"
#include "core/screen.hpp"
#include "event/interactible.hpp"

namespace MiniEngine {
namespace UI {
namespace Widgets {
/**
 * @brief A button is a widget that can be clicked by the player
 */
class ME_API Button : public Event::Interactible {
  public:
    // Constructors
    Button();
    virtual ~Button();

    // Operators
    Button &operator=(const Button &) = delete;

    // Getters
    SDL_Rect get_rect() const;
    SDL_Color get_background_color() const;
    SDL_Color get_foreground_color() const;
    SDL_Color get_contour_color() const;
    SDL_Rect get_text_position(SDL_Surface *) const;
    std::string get_text() const;

    // Overrides
    bool OnEvent(SDL_Event *event) override;
    void OnRender(Screen *screen) override;
    void OnUpdate(int time_elapsed) override;

    // Setters
    void set_rect(int x, int y, int w, int h);
    void set_position(int x, int y);
    void set_text_pos(std::string pos);
    void set_text_pos(int x, int y);
    void set_text_color(int r, int g, int b, int a = 255);
    void set_background_color(int r, int g, int b, int a = 255);
    void set_contour_color(int r, int g, int b);
    void set_size(int w, int h);
    void set_text(std::string text);

    void set_callback(std::function<void()> callback);

    void move(int, int);
    void set_text_offset(int, int);
    void resize(int, int);

    int update_layout();
    int update_layout(TTF_Font *font);
    int draw_contour(SDL_Surface *, SDL_Color);

    bool collide(int x, int y) const;

  private:
    SDL_Rect *m_rect;
    SDL_Rect *m_text_rect;
    SDL_Rect *m_absolute_text_position;
    SDL_Rect *m_text_offset;

    SDL_Color m_background_color;
    SDL_Color m_foreground_color;
    SDL_Color m_contour_color;

    SDL_Texture *m_background_texture;
    SDL_Texture *m_foreground_texture;
    std::function<void()> m_callback;

    int m_text_position;
    bool m_hover;
    std::string m_text;
    bool m_pos_as_text;
    TTF_Font *m_font;
};

} // namespace Widgets
} // namespace UI
} // namespace MiniEngine
