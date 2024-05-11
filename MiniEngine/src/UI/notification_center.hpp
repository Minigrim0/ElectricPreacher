#pragma once

#include "UI/widgets/notification.hpp"
#include "core/screen.hpp"
#include "graphics/tiles/tileset.hpp"

namespace MiniEngine {
namespace UI {
/**
 * @author Minigrim0
 * @brief The notification center is a widget that manages notifications
 * It can be used to display messages to the player
 */
class NotificationCenter {
  protected:
    NotificationCenter(Screen *screen);

  public:
    ~NotificationCenter();

    // Singleton pattern
    static NotificationCenter *create(Screen *screen);

    // Setter
    void set_default_font(std::string font);

    // Others
    void OnRender(Screen *);
    void OnUpdate(int time_elapsed);
    bool OnEvent(SDL_Event *event) { return false; }

    int create_notification(std::string text, Screen *screen, std::string font = "",
                            Uint16 lifetime = 10000);

  private:
    std::vector<Widgets::Notification *> m_notifications;
    Graphics::Tiling::TileSet *m_icons;

    std::string m_default_font;

    static NotificationCenter *nc_;
};
} // namespace UI
} // namespace MiniEngine
