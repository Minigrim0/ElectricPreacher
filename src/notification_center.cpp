#include "../includes/notification_center.h"

#include "../includes/screen.h"
#include "../includes/image_set.h"

NotificationCenter::NotificationCenter(Screen* sc)
:m_notifications(new std::vector<Notification>),
m_icons(new ImageSet),
m_position({0, 0, 0, 0})
{
    m_icons->set_image(sc, "assets/images/icons.png");
    m_icons->set_array();
}

NotificationCenter::~NotificationCenter(){

}

//Getters
SDL_Rect NotificationCenter::get_pos() const{
    return m_position;
}


//Setters
void NotificationCenter::set_pos(SDL_Rect position){
    m_position = position;
}

void NotificationCenter::set_pos(int x, int y){
    m_position.x = x;
    m_position.y = y;
}


//Others
int NotificationCenter::draw(Screen* screen){
    for(size_t x=0;x<m_notifications->size();x++){
        (*m_notifications)[x].draw(screen);
    }

    return 0;
}

int NotificationCenter::update(SDL_Event* event, Screen* screen){
    for(size_t x=0;x<m_notifications->size();x++){
        (*m_notifications)[x].update(event, screen);
    }

    return 0;
}

int NotificationCenter::create_notification(std::string text, Screen* screen){
    Notification notif;
    notif.set_position(10, 10);
    notif.set_text(text);

    notif.set_width(150);
    notif.init(screen, nullptr);
    m_notifications->push_back(notif);

    return 0;
}
