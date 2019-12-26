#include "../includes/constants.h"
#include "../includes/console.h"

Console::Console()
:m_history(),
m_input(nullptr),
m_send_button(nullptr),
m_font(nullptr)
{
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Creating new console " << std::endl;
    m_input = new TextInput;
    m_send_button = new Button();
    m_send_button->set_text("Send");
    m_send_button->set_rect({0, 0, 120, 20});
    m_send_button->set_text_pos("CENTER");
}

Console::Console(TTF_Font* font)
:m_history(),
m_input(nullptr),
m_send_button(nullptr),
m_font(font)
{
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Creating text input with font" << std::endl;
    m_input = new TextInput;
    m_send_button = new Button();
    m_send_button->set_text("Send");
    m_send_button->set_rect({0, 0, 120, 20});
    m_send_button->set_text_pos("CENTER");
}

Console::~Console(){
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> deleting console" << std::endl;
    delete m_input;
}

// Setters

int Console::set_font(TTF_Font* font){
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Setting font" << std::endl;
    m_font = font;
    return 0;
}

int Console::set_font(std::string font_path, int font_size){
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Setting console font from path : " << font_path << std::endl;
    m_font = TTF_OpenFont(font_path.c_str(), 20);
    if(m_font == nullptr){
        std::cout << "Error loading font " << font_path << " : " << TTF_GetError() << std::endl;
        return 1;
    }
    return 0;
}

// Others

int Console::draw(Screen* screen){
    for(long unsigned int x=0;x<(m_history.size()<5?m_history.size():5);x++){
        m_history[x].draw(screen);
    }
    m_input->draw(screen);
    return 0;
}

int Console::update(SDL_Event event){
    m_input->update(event);
    return 0;
}

int Console::update_layout(Screen* screen){
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Updating layout" << std::endl;
    if(m_font == nullptr){
        std::cout << "Error updating console layout : Font has not been loaded" << std::endl;
        return 1;
    }
    m_input->update_image(screen, m_font);
    return m_send_button->update_layout(screen, m_font);
}
