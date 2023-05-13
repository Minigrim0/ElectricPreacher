#pragma once

#include <SDL_stdinc.h>
#include <SDL_ttf.h>

#include "UI/widgets.hpp"

#include "screen/tileset.hpp"
#include "screen/notification.hpp"
#include "screen/screen.hpp"

class NotificationCenter : public Widget
{
protected:
    NotificationCenter();

public:
    ~NotificationCenter();

    // Singleton pattern
    static NotificationCenter *GetInstance();

    // Setter
    void set_default_font(std::string font);

    // Others
    int draw(Screen *) override;
    int update(SDL_Event *, Screen *) override;
    int create_notification(std::string text, Screen *screen, std::string font = "", Uint16 lifetime = 10000);

private:
    std::vector<Notification *> m_notifications;
    TileSet *m_icons;

    std::string m_default_font;

    static NotificationCenter *nc_;
};
