#include <fstream>
#include <SDL2/SDL.h>

#include "../includes/json/json.h"
#include "../includes/window.h"
#include "../includes/button.h"
#include "../includes/screen.h"
#include "../includes/constants.h"


Window::Window(){}

Window::~Window(){}

// Returns the current state of the window
bool Window::is_running() const{
    return m_window_running;
}

// Returns the name (identifier) of the window
std::string Window::get_title() const{
    return m_window_name;
}

// Defines wether the window is running or not
void Window::set_running(bool running){
    m_window_running = running;
}

int Window::set_font(std::string path){
    int sizes[] = {12, 15, 20, 25, 30};
    int result = 0;
    for(int x=0;x<5;x++){
        m_fonts[x] = TTF_OpenFont(path.c_str(), sizes[x]);
        if(m_fonts[x] == NULL){
            result = 1;
            std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
        }
    }
    return result;
}

// Create a button that holds the title
void Window::set_title(Screen* screen, Json::Value title){
    m_window_name = title["window_name"].asString();
    m_title = new Button;
    m_title->set_text(title["text"].asString());
    m_title->set_position(0, 0);
    m_title->set_size(
        screen->get_width(),
        screen->get_height()
    );
    m_title->set_text_color(
        title["text-color"]["r"].asInt(),
        title["text-color"]["g"].asInt(),
        title["text-color"]["b"].asInt()
    );
    m_title->set_background_color(0, 0, 0, 0);
    if(title["text_position_type"].asString() == "txt")
        m_title->set_text_pos(
            title["text-position"].asString()
        );
    else
        m_title->set_text_pos(
            title["text-position_x"].asInt(),
            title["text-position_y"].asInt()
        );

    //Finally update the button image
    m_title->update_layout(
        screen,
        m_fonts[title["font_size"].asInt()]
    );
}

// Add an already created button to the list of buttons
void Window::add_button(Button* newButton){
    m_buttons.push_back(newButton);
}

// Add a button from a parsed json object
int Window::add_button(Screen* screen, Json::Value buttons){
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
        m_buttons.back()->update_layout(
            screen,
            m_fonts[buttons[index]["font_size"].asInt()]
        );    
    }
    return 0;
}

// Updates the window
void Window::update(){}

// Draws the window to the screen
void Window::draw(Screen* screen){
    for(unsigned i = 0; i < m_buttons.size(); i++){
        m_buttons[i]->draw(screen);
    }
}

// Create the window from a json file
int Window::createfrom(Screen* screen, std::string JSONsource){
    std::ifstream json_in(JSONsource.c_str());
    Json::Value root;
    json_in >> root;

    // Setup Buttons
    const Json::Value buttons = root["Buttons"];
    this->add_button(screen, buttons);

    // Setup title
    const Json::Value title = root["Title"];
    this->set_title(screen, title);

    json_in.close();
    return 0;
}
