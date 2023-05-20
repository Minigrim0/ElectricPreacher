#pragma once

#include <SDL_stdinc.h>
#include <SDL_ttf.h>

#include "graphics/tileset.hpp"
#include "UI/widgets/notification.hpp"
#include "core/screen.hpp"

/**
 * @author Minigrim0
 * @brief The notification center is a widget that manages notifications
 * It can be used to display messages to the player
 */
namespace MiniEngine {
    namespace UI {
        class NotificationCenter {
        protected:
            NotificationCenter(Screen *screen);

        public:
            ~NotificationCenter();

            // Singleton pattern
            static NotificationCenter *Create(Screen *screen);

            // Setter
            void set_default_font(std::string font);

            // Others
            int draw(Screen *);
            int update(SDL_Event *, Screen *);
            int create_notification(std::string text, Screen *screen, std::string font = "", Uint16 lifetime = 10000);

        private:
            std::vector<Widgets::Notification *> m_notifications;
            Graphics::TileSet *m_icons;

            std::string m_default_font;

            static NotificationCenter *nc_;
        };
    }
}
