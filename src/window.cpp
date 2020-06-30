#include "../includes/window.h"
#include "../includes/button.h"
#include "../includes/screen.h"

Window::Window(){}

Window::~Window(){}

bool Window::is_running() const{
    return m_window_running;
}

std::string Window::get_title() const{
    return m_window_title;
}

void Window::set_running(bool running){
    m_window_running = running;
}

void Window::set_title(std::string title){
    m_window_title = title;
}

int Window::add_button(Button* newButton){
    m_buttons.push_back(newButton);

    return 0;
}

void Window::update(){}

void Window::draw(Screen* screen){
    for(unsigned i = 0; i < m_buttons.size(); i++){
        m_buttons[i]->draw(screen);
    }
}

int Window::createfrom(std::string JSONsource){
    
}
