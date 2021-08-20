#include "../includes/notification_center.hpp"

#include "../includes/screen.hpp"
#include "../includes/image_set.hpp"

#include "constants.hpp"

NotificationCenter::NotificationCenter(Screen* sc, std::string default_font)
:m_notifications(std::vector<Notification*>()),
m_icons(new ImageSet),
m_default_font(default_font)
{
    m_icons->set_image(sc, "assets/images/icons.png");
    m_icons->set_array();
}

NotificationCenter::~NotificationCenter(){
    delete m_icons;
}

//Others
int NotificationCenter::draw(Screen* screen){
    for(size_t x=0;x<m_notifications.size();x++){
        m_notifications[x]->set_offset(static_cast<int>(x) * 51);
        m_notifications[x]->draw(screen);
    }

    return 0;
}

int NotificationCenter::update(SDL_Event* event, Screen* screen){
    for(size_t x=0;x<m_notifications.size();x++){
        if(m_notifications[x]->update(event, screen) == 0){
            m_notifications.erase(m_notifications.begin() + static_cast<long int>(x));
        }
    }

    return 0;
}

int NotificationCenter::create_notification(std::string text, Screen* screen, std::string font, Uint16 lifetime){
    m_notifications.push_back(new Notification);
    m_notifications.back()->set_position(10, 10);
    m_notifications.back()->set_text(text);
    m_notifications.back()->set_lifetime(lifetime);

    m_notifications.back()->set_width(150);
    if(font != "")
        m_notifications.back()->init(screen, font);
    else
        m_notifications.back()->init(screen, m_default_font);

    return 0;
}
