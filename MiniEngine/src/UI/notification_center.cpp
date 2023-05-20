#include "UI/notification_center.hpp"

#include "core/screen.hpp"
#include "graphics/tileset.hpp"
#include "UI/widgets/notification.hpp"

namespace MiniEngine {
    namespace UI {
        NotificationCenter* NotificationCenter::nc_ = nullptr;

        NotificationCenter::NotificationCenter(Screen* screen)
            :m_notifications(std::vector<Widgets::Notification*>()),
            m_icons(new Graphics::TileSet),
            m_default_font("")
        {
            m_icons->load(screen, "assets/maps/tilesets/icons.tsx");
        }

        NotificationCenter::~NotificationCenter() {
            delete m_icons;
        }

        NotificationCenter* NotificationCenter::Create(Screen* screen) {
            return new NotificationCenter(screen);
        }

        void NotificationCenter::set_default_font(std::string font) {
            m_default_font = font;
        }

        // Others
        int NotificationCenter::draw(Screen* screen) {
            for (size_t x = 0; x < m_notifications.size(); x++) {
                m_notifications[x]->set_offset(static_cast<int>(x) * 51);
                m_notifications[x]->OnRender(screen);
            }

            return 0;
        }

        int NotificationCenter::update(int time_elapsed) {
            for (size_t x = 0; x < m_notifications.size(); x++) {
                m_notifications[x]->OnUpdate(time_elapsed)
                if(!m_notifications[x]->is_alive()) {
                    m_notifications.erase(m_notifications.begin() + static_cast<long int>(x));
                }
            }

            return 0;
        }

        int NotificationCenter::create_notification(std::string text, Screen* screen, std::string font, Uint16 lifetime) {
            m_notifications.push_back(new Widgets::Notification);
            m_notifications.back()->set_position(10, 10);
            m_notifications.back()->set_text(text);
            m_notifications.back()->set_lifetime(lifetime);

            m_notifications.back()->set_width(150);
            if (font != "")
                m_notifications.back()->init(screen, font);
            else
                m_notifications.back()->init(screen, m_default_font);

            return 0;
        }

    }
}
