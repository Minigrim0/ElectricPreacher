#include "button.hpp"

#include "core/application.hpp"
#include "core/log.hpp"

namespace MiniEngine::UI::Widgets {
// Constructors
Button::Button()
    : m_rect(new SDL_Rect), m_text_rect(new SDL_Rect), m_absolute_text_position(new SDL_Rect),
      m_text_offset(new SDL_Rect), m_text_position(4), m_hover(false),
      m_background_color({0, 0, 0, 0}), m_foreground_color({255, 255, 255, 0}),
      m_contour_color({255, 255, 255, 0}), m_background_texture(nullptr),
      m_foreground_texture(nullptr), m_text(""), m_pos_as_text(true), m_font(nullptr) {
    // The offset should be default 0
    m_text_offset->x = 0;
    m_text_offset->y = 0;
}

Button::~Button() {
    delete m_rect;
    SDL_DestroyTexture(m_background_texture);
    SDL_DestroyTexture(m_foreground_texture);
}

// Callback
bool Button::OnEvent(SDL_Event *event) {
    switch (event->type) {
    case SDL_MOUSEMOTION:
        if (m_hover != collide(event->motion.x, event->motion.y)) {
            m_hover = !m_hover;
            update_layout(m_font);
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (collide(event->button.x, event->button.y)) {
            if (m_callback) {
                m_callback();
            } else {
                ME_CORE_WARN("Button has no callback");
            }
            return true; // Event was handled
        }
        break;
    default:
        break;
    }
    return false;
}

/**
 * @brief Draws the button on the screen
 *
 * @param screen The screen on which to draw
 * @return int 0 on success, -1 on error
 */
void Button::OnRender(Screen *screen) {
    SDL_RenderCopy(screen->get_renderer(), m_background_texture, NULL, m_rect);
    SDL_RenderCopy(screen->get_renderer(), m_foreground_texture, NULL, m_text_rect);
}

void Button::OnUpdate(int time_elapsed) { return; }

// Getters
SDL_Rect Button::get_rect() const { return *m_rect; }

SDL_Color Button::get_background_color() const { return m_background_color; }

SDL_Color Button::get_foreground_color() const { return m_foreground_color; }

SDL_Color Button::get_contour_color() const { return m_contour_color; }

SDL_Rect Button::get_text_position(SDL_Surface *tmp_text) const {
    SDL_Rect position = {0, 0, 0, 0};
    if (m_pos_as_text) {
        switch (m_text_position) {
        case 0:
            position.x = 0;
            position.y = 0;
            break;
        case 1:
            position.x = (m_rect->w - tmp_text->w) / 2;
            position.y = 0;
            break;
        case 2:
            position.x = m_rect->w - tmp_text->w;
            position.y = 0;
            break;
        case 3:
            position.x = 0;
            position.y = (m_rect->h - tmp_text->h) / 2;
            break;
        case 4:
            position.x = (m_rect->w - tmp_text->w) / 2;
            position.y = (m_rect->h - tmp_text->h) / 2;
            break;
        case 5:
            position.x = m_rect->w - tmp_text->w;
            position.y = (m_rect->h - tmp_text->h) / 2;
            break;
        case 6:
            position.x = 0;
            position.y = m_rect->h - tmp_text->h;
            break;
        case 7:
            position.x = (m_rect->w - tmp_text->w) / 2;
            position.y = m_rect->h - tmp_text->h;
            break;
        case 8:
            position.x = m_rect->w - tmp_text->w;
            position.y = m_rect->h - tmp_text->h;
            break;
        default:
            position.x = 0;
            position.y = 0;
        }
    }
    return position;
}

std::string Button::get_text() const { return m_text; }

// Setters
void Button::set_rect(int x, int y, int w, int h) {
    m_rect->x = x;
    m_rect->y = y;
    m_rect->w = w;
    m_rect->h = h;

    m_text_rect->x = x;
    m_text_rect->y = y;
}

void Button::set_position(int x, int y) {
    m_rect->x = x;
    m_rect->y = y;

    m_text_rect->x = x;
    m_text_rect->y = y;
}

void Button::set_text_pos(std::string position) {
    m_pos_as_text = true;

    std::string arr[9] = {"TOP_LEFT",  "TOP_CENTER", "TOP_RIGHT",  "MID_LEFT", "MID_CENTER",
                          "MID_RIGHT", "BOT_LEFT",   "BOT_CENTER", "BOT_RIGHT"};
    for (int x = 0; x < 9; x++)
        if (position == arr[x])
            m_text_position = x;
}

void Button::set_text_pos(int x, int y) {
    m_pos_as_text = false;
    m_absolute_text_position->x = x;
    m_absolute_text_position->y = y;
}

void Button::set_text_color(int r, int g, int b, int a) {
    m_foreground_color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b),
                          static_cast<Uint8>(a)

    };
}

void Button::set_background_color(int r, int g, int b, int a) {
    m_background_color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b),
                          static_cast<Uint8>(a)};
}

void Button::set_contour_color(int r, int g, int b) {
    m_contour_color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), 0};
}

void Button::set_size(int w, int h) {
    m_rect->w = w;
    m_rect->h = h;
}

void Button::set_text(std::string text) { m_text = text; }

void Button::set_callback(std::function<void()> callback) { m_callback = callback; }

void Button::move(int off_x, int off_y) {
    m_rect->x += off_x;
    m_rect->y += off_y;

    m_text_rect->x += off_x;
    m_text_rect->y += off_y;
}

void Button::set_text_offset(int off_x, int off_y) {
    if (m_pos_as_text) { // Offset is used only with relative positioning
        m_text_offset->x += off_x;
        m_text_offset->y += off_y;
    }
}

void Button::resize(int off_w, int off_h) {
    m_rect->x += off_w;
    m_rect->y += off_h;
}

/**
 * @brief Updates the layout of a button
 *
 * @param screen
 * @param font
 * @return int
 */
int Button::update_layout() {
    Screen *screen = Application::GetInstance()->get_screen();
    TTF_Font *font = screen->get_font("default");
    return update_layout(font);
}

int Button::update_layout(TTF_Font *font) {
    m_font = font;

    Screen *screen = Application::GetInstance()->get_screen();
    SDL_Surface *tmp_image = SDL_CreateRGBSurface(0, m_rect->w, m_rect->h, 32, 0, 0, 0, 0);
    SDL_Surface *tmp_text;

    if (m_hover) {
        SDL_FillRect(tmp_image, NULL,
                     SDL_MapRGB(tmp_image->format, m_foreground_color.r, m_foreground_color.g,
                                m_foreground_color.b));
        tmp_text = TTF_RenderText_Blended(font, m_text.c_str(), m_background_color);
    } else {
        SDL_FillRect(tmp_image, NULL,
                     SDL_MapRGB(tmp_image->format, m_background_color.r, m_background_color.g,
                                m_background_color.b));
        tmp_text = TTF_RenderText_Blended(font, m_text.c_str(), m_foreground_color);
    }

    if (tmp_text == NULL) {
        ME_CORE_ERROR("Error while rendering text : {0}", TTF_GetError());
        return -1;
    }
    SDL_Rect position_offset = get_text_position(tmp_text);
    m_text_rect->x = m_rect->x + position_offset.x + m_text_offset->x;
    m_text_rect->y = m_rect->y + position_offset.y + m_text_offset->y;
    m_text_rect->w = tmp_text->w;
    m_text_rect->h = tmp_text->h;

    if (draw_contour(tmp_image, m_contour_color) != 0)
        ME_CORE_ERROR("Error while drawing contour : {0}", SDL_GetError());

    m_background_texture = screen->surf2Text(tmp_image);
    if (m_background_color.a != 255) {
        SDL_SetTextureBlendMode(m_background_texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(m_background_texture, m_background_color.a);
    }
    m_foreground_texture = screen->surf2Text(tmp_text);
    if (m_foreground_color.a != 255) {
        SDL_SetTextureBlendMode(m_foreground_texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(m_foreground_texture, m_foreground_color.a);
    }

    SDL_FreeSurface(tmp_text);
    SDL_FreeSurface(tmp_image);
    return 0;
}

int Button::draw_contour(SDL_Surface *surf, SDL_Color color) {
    SDL_Surface *horizontal_line = SDL_CreateRGBSurface(0, surf->w, 1, 32, 0, 0, 0, 0);
    SDL_Surface *vertical_line = SDL_CreateRGBSurface(0, 1, surf->h, 32, 0, 0, 0, 0);
    SDL_FillRect(horizontal_line, NULL, SDL_MapRGB(surf->format, color.r, color.g, color.b));
    SDL_FillRect(vertical_line, NULL, SDL_MapRGB(surf->format, color.r, color.g, color.b));

    SDL_Rect position = {0, 0, 0, 0};
    SDL_BlitSurface(horizontal_line, NULL, surf, &position);
    SDL_BlitSurface(vertical_line, NULL, surf, &position);

    position = {surf->w - 1, 0, 0, 0};
    SDL_BlitSurface(vertical_line, NULL, surf, &position);

    position = {0, surf->h - 1, 0, 0};
    SDL_BlitSurface(horizontal_line, NULL, surf, &position);

    SDL_FreeSurface(horizontal_line);
    SDL_FreeSurface(vertical_line);

    return 0;
}

bool Button::collide(int x, int y) const {
    if (x > m_rect->x && x < m_rect->x + m_rect->w)
        if (y > m_rect->y && y < m_rect->y + m_rect->h)
            return true;
    return false;
}
} // namespace MiniEngine::UI::Widgets
