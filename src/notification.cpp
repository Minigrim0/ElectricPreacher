#include "../includes/notification.h"

//Constructors
Notification::Notification()
:m_content(""),
m_background(nullptr),
m_text_texture(nullptr),
m_icon(nullptr)
{

}

Notification::~Notification(){

}


int Notification::draw(Screen*){
    return 0;
}

int Notification::update(SDL_Event*, Screen*){
    return 0;
}
