#include "../includes/container.hpp"

Container::Container()
:m_rect({0, 0, 0, 0}),
m_widgets(std::vector<Widget*>())
{}

Container::~Container(){}

// Others
int Container::draw(Screen* screen){
    return 0;
}

int Container::update(SDL_Event* event, Screen* screen){
    return 0;
}
