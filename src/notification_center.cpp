#include "../includes/notification_center.h"

NotificationCenter::NotificationCenter()
:m_notifications(std::vector<Notification>()),
m_icons(std::vector<SDL_Texture*>())
{}

NotificationCenter::~NotificationCenter(){

}


int NotificationCenter::draw(Screen*){
    return 0;
}

int NotificationCenter::update(SDL_Event*, Screen*){
    return 0;
}
