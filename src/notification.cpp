#include "../includes/notification.h"

//Constructors
Notification::Notification()
:m_content(""),
m_position({0, 0, 0, 0}),
m_progress_bar_color({0, 0, 0, 0}),
m_text_color({0, 0, 0, 0}),
m_background(nullptr),
m_text_texture(nullptr),
m_icon(nullptr),
m_total_lifetime(10000),
m_current_lifetime(0),
m_alpha(255)
{}

Notification::~Notification(){

}


int Notification::draw(Screen*){
    return 0;
}

int Notification::update(SDL_Event*, Screen*){
    return 0;
}

void Notification::init(Screen* screen){

}
