#ifndef notif_center_h
    #define notif_center_h

#include "widgets.h"
#include "notification.h"
#include "image_set.h"
#include "screen.h"

class NotificationCenter: public Widget{
    public:
        NotificationCenter(Screen*);
        ~NotificationCenter();

        // Getters
        SDL_Rect get_pos() const;

        // Setters
        void set_pos(SDL_Rect);
        void set_pos(int, int);
        void set_size(int, int);

        // Others
        int draw(Screen*) override;
        int update(SDL_Event*, Screen*) override;
        int create_notification(std::string, Screen*);

    private:
        std::vector<Notification>* m_notifications;
        ImageSet* m_icons;

        SDL_Rect m_position;
};

#endif
