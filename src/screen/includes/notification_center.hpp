#ifndef notif_center_h
    #define notif_center_h

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>

#include "../../UI/includes/widgets.hpp"

#include "image_set.hpp"
#include "notification.hpp"
#include "screen.hpp"

class NotificationCenter: public Widget{
    public:
        NotificationCenter(Screen*, std::string default_font);
        ~NotificationCenter();

        // Others
        int draw(Screen*) override;
        int update(SDL_Event*, Screen*) override;
        int create_notification(std::string text, Screen* screen, std::string font="", Uint16 lifetime=10000);

    private:
        std::vector<Notification*> m_notifications;
        ImageSet* m_icons;

        std::string m_default_font;
};

#endif
