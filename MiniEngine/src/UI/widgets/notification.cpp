#include "UI/widgets/notification.hpp"

#include "core/log.hpp"

namespace MiniEngine {
namespace UI {
namespace Widgets {
// Constructors
Notification::Notification()
    : m_content(""), m_position({0, 0, 0, 0}), m_offset(0), m_progress_bar_color({0, 0, 0, 0}),
      m_text_color({0, 0, 0, 0}), m_background(nullptr), m_text_texture(nullptr),
      m_progress_bar(nullptr), m_icon(nullptr), m_total_lifetime(10000), m_current_lifetime(0),
      m_alpha(255) {}

Notification::~Notification() {
    SDL_DestroyTexture(m_background);
    SDL_DestroyTexture(m_text_texture);
    // SDL_DestroyTexture(m_progress_bar);
}

// Setters
void Notification::set_position(int x, int y) {
    m_position.x = x;
    m_position.y = y;
}

void Notification::set_text(std::string text) { m_content = text; }

void Notification::set_icon(SDL_Texture *tex) { m_icon = tex; }

void Notification::set_lifetime(Uint16 lifetime) { m_total_lifetime = lifetime; }

void Notification::set_offset(int offset) { m_offset = offset; }

void Notification::set_width(int w) { m_position.w = w; }

// Getters
int Notification::get_height() const { return m_position.h; }

bool Notification::is_alive() const { return m_current_lifetime < m_total_lifetime; }

bool Notification::OnEvent(SDL_Event *event) {
    return false; // Notifications are not interactible (yet)
}

void Notification::OnRender(Screen *sc) {
    double percent_death =
        (1.0 - (static_cast<float>(m_current_lifetime) / static_cast<float>(m_total_lifetime))) *
        500.0;

    m_position.y += m_offset;
    SDL_Rect pbdst = {m_position.x, m_position.y + 50, static_cast<int>(percent_death), 1};
    SDL_RenderCopy(sc->get_renderer(), m_background, NULL, &m_position);
    SDL_RenderCopy(sc->get_renderer(), m_progress_bar, NULL, &pbdst);
    m_position.y -= m_offset;
}

void Notification::OnUpdate(int time_elapsed) {
    m_current_lifetime += static_cast<Uint16>(time_elapsed);
}

void Notification::init(Screen *screen, std::string font) {
    SDL_Surface *tmp_text = screen->renderTextBlend(m_content, screen->get_font(font));
    m_text_texture = SDL_CreateTextureFromSurface(screen->get_renderer(), tmp_text);

    m_background = SDL_CreateTexture(screen->get_renderer(), SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_TARGET, 500, 50);
    m_progress_bar = SDL_CreateTexture(screen->get_renderer(), SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_TARGET, 1, 1);

    if (m_background == nullptr) {
        ME_CORE_ERROR("Failed to create a texture : {0}", SDL_GetError());
        return;
    }

    SDL_SetTextureBlendMode(m_background, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(screen->get_renderer(), m_background);

    SDL_SetRenderDrawColor(screen->get_renderer(), 150, 150, 150, 150);
    SDL_RenderFillRect(screen->get_renderer(), nullptr);
    SDL_SetRenderDrawColor(screen->get_renderer(), 0, 0, 0, 255);
    SDL_Rect rect = {5, 5, 40, 40};
    SDL_RenderFillRect(screen->get_renderer(), &rect);

    // Draw the text onto the background
    SDL_Rect txtdst = {60, 20, 0, 0};
    SDL_QueryTexture(m_text_texture, nullptr, nullptr, &txtdst.w, &txtdst.h);
    SDL_RenderCopy(screen->get_renderer(), m_text_texture, nullptr, &txtdst);

    m_position.w = 500;
    m_position.h = 50;

    // Fill the progress bar with a gray tray
    SDL_SetRenderTarget(screen->get_renderer(), m_progress_bar);

    SDL_SetRenderDrawColor(screen->get_renderer(), 255, 255, 255, 0);
    SDL_RenderFillRect(screen->get_renderer(), nullptr);
    SDL_SetRenderDrawColor(screen->get_renderer(), 0, 0, 0, 255);

    SDL_SetRenderTarget(screen->get_renderer(), nullptr);
}

} // namespace Widgets
} // namespace UI
} // namespace MiniEngine
