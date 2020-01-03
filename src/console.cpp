#include "../includes/constants.h"
#include "../includes/console.h"

Console::Console()
:m_rect({0, 0, 0, 0}),
m_history(),
m_input(nullptr),
m_send_button(nullptr),
m_font(nullptr),
m_nb_visible_lines(5),
m_line_height(0)
{
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ <<
        "> Creating new console " << std::endl;
    m_input = new TextInput;
    m_send_button = new Button();
    m_send_button->set_text("Send");
    m_send_button->set_rect({0, 0, 120, 20});
    m_send_button->set_text_pos("CENTER");
}

Console::Console(int x, int y)
:m_rect({x, y, 0, 0}),
m_history(),
m_input(nullptr),
m_send_button(nullptr),
m_font(nullptr),
m_nb_visible_lines(5),
m_line_height(0)
{
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ <<
        "> Creating new console " << std::endl;
    m_input = new TextInput;
    m_send_button = new Button();
    m_send_button->set_text("Send");
    m_send_button->set_rect({0, 0, 120, 20});
    m_send_button->set_text_pos("CENTER");
}

Console::Console(int x, int y, int w)
:m_rect({x, y, w, w}),
m_history(),
m_input(new TextInput),
m_send_button(new Button),
m_font(nullptr),
m_nb_visible_lines(5),
m_line_height(0)
{
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ <<
        "> Creating new console " << std::endl;
    m_send_button->set_text("Send");
    m_send_button->set_text_pos("CENTER");
}

Console::Console(int x, int y, int w, int h)
:m_rect({x, y, w, h}),
m_history(),
m_input(nullptr),
m_send_button(nullptr),
m_font(nullptr),
m_nb_visible_lines(5),
m_line_height(0)
{
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ <<
        "> Creating new console " << std::endl;
    m_input = new TextInput;
    m_send_button = new Button();
    m_send_button->set_text("Send");
    m_send_button->set_rect({0, 0, 120, 20});
    m_send_button->set_text_pos("CENTER");
}

Console::Console(TTF_Font* font)
:m_rect({0, 0, 0, 0}),
m_history(),
m_input(nullptr),
m_send_button(nullptr),
m_font(font),
m_nb_visible_lines(5),
m_line_height(0)
{
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ <<
        "> Creating console with font" << std::endl;
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

void Console::set_position(int x, int y){
    m_rect.x = x;
    m_rect.y = y;
}

void Console::set_size(int w, int h){
    m_rect.w = w;
    m_rect.h = h;
}

int Console::set_font(TTF_Font* font){
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Setting font" << std::endl;
    m_font = font;
    return 0;
}

int Console::set_font(std::string font_path, int font_size){
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Setting console font from path : " << font_path << std::endl;
    m_font = TTF_OpenFont(font_path.c_str(), font_size);
    if(m_font == nullptr){
        std::cout << "Error loading font " << font_path << " : " << TTF_GetError() << std::endl;
        return 1;
    }
    return 0;
}

// Others

void Console::init(Screen* screen){
    if(!(m_rect.w && m_rect.h)){
        std::cout << "Error initializing the console, missing size !" << std::endl;
    }

    m_line_height = static_cast<int>(static_cast<float>(m_rect.w)*0.1);
    m_nb_visible_lines = static_cast<int>(static_cast<float>(m_rect.h)/static_cast<float>(m_line_height));
    std::cout << "Nb lines in the console :" << m_nb_visible_lines << std::endl;

    int width = static_cast<int>(static_cast<float>(m_rect.w)*0.8);
    int send_width = static_cast<int>(static_cast<float>(m_rect.w)*0.2);

    int pos_y = m_line_height*m_nb_visible_lines;

    m_input->set_position(0, pos_y);
    m_input->set_text_size(width, m_line_height);

    m_send_button->set_rect({width, pos_y, send_width, m_line_height});

    m_send_button->update_layout(screen, m_font);
}

int Console::draw(Screen* screen){
    int max = static_cast<int>(m_history.size())<m_nb_visible_lines?static_cast<int>(m_history.size()):m_nb_visible_lines;
    for(int x=0;x<max;x++){
        m_history[static_cast<long unsigned int>(x)]->draw(screen);//draw_offset_y(screen, x*30);
    }
    m_input->draw(screen);
    m_send_button->draw(screen);
    return 0;
}

int Console::update(SDL_Event* event, Screen* screen){
    if(m_input->update(event, screen, m_font) == 1 || m_send_button->update(event, screen) == 1){
        int max = static_cast<int>(m_history.size())<m_nb_visible_lines?static_cast<int>(m_history.size()):m_nb_visible_lines;
        for(int x=0;x<max;x++)
            m_history[static_cast<long unsigned int>(x)]->move(0, -m_line_height);

        if(DEBUG)
            std::cout << __PRETTY_FUNCTION__ << "> Processing input text" << std::endl;

        Button* tmp_button = new Button();
        tmp_button->set_rect({0, m_line_height*(m_nb_visible_lines-1), m_rect.w, m_line_height});
        tmp_button->set_text(m_input->get_text());
        tmp_button->set_contour_color(255, 0, 0);
        tmp_button->update_layout(screen, m_font);
        m_history.push_back(tmp_button);
    }
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
