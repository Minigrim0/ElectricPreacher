#include <fstream>
#include <SDL2/SDL.h>

#include "../includes/json/json.h"
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

int Window::createfrom(Screen* screen, std::string JSONsource){
    std::ifstream json_in(JSONsource.c_str());
    Json::Value root;
    json_in >> root;

    //Setup Buttons
    const Json::Value buttons = root["Buttons"];
    for (unsigned int index=0;index<buttons.size();++index){
        m_buttons.push_back(new Button);
        m_buttons.back()->set_text(buttons[index]["name"].asString());

        m_buttons.back()->set_position(
            buttons[index]["position_x"].asInt(),
            buttons[index]["position_y"].asInt()
        );

        m_buttons.back()->set_size(
            buttons[index]["size_x"].asInt(),
            buttons[index]["size_y"].asInt()
        );

        m_buttons.back()->set_text_color(
            buttons[index]["text-color"]["r"].asInt(),
            buttons[index]["text-color"]["g"].asInt(),
            buttons[index]["text-color"]["b"].asInt()
        );

        m_buttons.back()->set_background_color(
            buttons[index]["background-color"]["r"].asInt(),
            buttons[index]["background-color"]["g"].asInt(),
            buttons[index]["background-color"]["b"].asInt()
        );

        m_buttons.back()->set_contour_color(
            buttons[index]["contour-color"]["r"].asInt(),
            buttons[index]["contour-color"]["g"].asInt(),
            buttons[index]["contour-color"]["b"].asInt()
        );

        //Set text-position, via text or absolute coordinates
        if(buttons[index]["text_position_type"].asString() == "txt")
            m_buttons.back()->set_text_pos(
                buttons[index]["text-position"].asString()
            );
        else
            m_buttons.back()->set_text_pos(
                buttons[index]["text-position_x"].asInt(),
                buttons[index]["text-position_y"].asInt()
            );

        //Finally update the button image
        /*m_buttons.back()->update_layout(
            screen,
            m_fonts[buttons[index]["font_size"].asInt()]
        );*/
    }

    //Setup grid
    const Json::Value grid = root["Grid"];
    //m_grid_pos.x = grid["position_x"].asInt();
    //m_grid_pos.y = grid["position_y"].asInt();

    json_in.close();
    return 0;
}
