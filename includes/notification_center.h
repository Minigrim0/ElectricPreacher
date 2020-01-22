#ifndef notif_center_h
    #define notif_center_h

#include "widgets.h"
#include "notification.h"

class NotificationCenter: public Widget{
    public:
        NotificationCenter();
        ~NotificationCenter();

        // Getters

        // Setters

        // Others
        int draw(Screen*) override;
        int update(SDL_Event*, Screen*) override;

    private:
        std::vector<Notification> m_notifications;
        std::vector<SDL_Texture*> m_icons;
};

#endif
