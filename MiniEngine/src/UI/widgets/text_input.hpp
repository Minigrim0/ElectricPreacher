#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "core/screen.hpp"
#include "widgets.hpp"

/**
 * @brief A text input is a widget that can be used to get text input from the player
 */
namespace MiniEngine
{
    namespace UI
    {
        namespace Widgets
        {
class TextInput : public Widget
{
public:
    TextInput();
    ~TextInput();

    TextInput &operator=(const TextInput &);

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

    // Others
    int draw(Core::Screen *) override;
    int update(SDL_Event *, Core::Screen *) override;

    void update_image(Core::Screen *);
    void flush(Core::Screen *);

private:
    SDL_Texture *m_tex;
    SDL_Texture *m_cursor;
    SDL_Surface *m_background_image;
    SDL_Rect m_rect;
    TTF_Font *m_font;

    std::string m_current_input;
    Sint32 m_cursor_pos;
    Sint32 m_selection_len;

    bool m_is_active;
};

        }}}