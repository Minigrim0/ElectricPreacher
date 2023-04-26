#include "UI/console.hpp"

#include "constants.hpp"


Console::Console()
:m_rect({0, 0, 0, 0}),
m_history(),
m_input(new TextInput),
m_send_button(new Button),
m_font(nullptr),
m_background_texture(nullptr),
m_nb_visible_lines(5),
m_line_height(0),
m_alpha(125)
{
    init_send_button();
}

Console::Console(int x, int y)
:m_rect({x, y, 0, 0}),
m_history(),
m_input(new TextInput),
m_send_button(new Button),
m_font(nullptr),
m_background_texture(nullptr),
m_nb_visible_lines(5),
m_line_height(0),
m_alpha(125)
{
    init_send_button();
}

Console::Console(int x, int y, int w)
:m_rect({x, y, w, w}),
m_history(),
m_input(new TextInput),
m_send_button(new Button),
m_font(nullptr),
m_background_texture(nullptr),
m_nb_visible_lines(5),
m_line_height(0),
m_alpha(125)
{
    init_send_button();
}

Console::Console(int x, int y, int w, int h)
:m_rect({x, y, w, h}),
m_history(),
m_input(new TextInput),
m_send_button(new Button),
m_font(nullptr),
m_background_texture(nullptr),
m_nb_visible_lines(5),
m_line_height(0),
m_alpha(125)
{
    init_send_button();
}

Console::Console(TTF_Font* font)
:m_rect({0, 0, 0, 0}),
m_history(),
m_input(new TextInput),
m_send_button(new Button),
m_font(font),
m_background_texture(nullptr),
m_nb_visible_lines(5),
m_line_height(0),
m_alpha(125)
{
    m_input->set_font(font);
    init_send_button();
}

Console::~Console(){
    delete m_input;
    delete m_send_button;
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
    m_font = font;
    return 0;
}

int Console::set_font(std::string font_path, int font_size){
    m_font = TTF_OpenFont(font_path.c_str(), font_size);
    if(m_font == nullptr){
        std::cout << "Error loading font " << font_path << " : " << TTF_GetError() << std::endl;
        return 1;
    }
    m_input->set_font(font_path, 70);
    return 0;
}

// Others
void Console::init(Screen* screen){
    if(!(m_rect.w && m_rect.h)){
        std::cout << "Error initializing the console, missing size !" << std::endl;
    }

    m_line_height = static_cast<int>(static_cast<float>(m_rect.w)*0.1);
    m_nb_visible_lines = static_cast<int>(static_cast<float>(m_rect.h)/static_cast<float>(m_line_height)) - 1;

    int width = static_cast<int>(static_cast<float>(m_rect.w)*0.9);
    int send_width = static_cast<int>(static_cast<float>(m_rect.w)*0.1);

    int pos_y = m_rect.y + m_line_height*(m_nb_visible_lines);

    m_input->set_position(m_rect.x, pos_y);
    m_input->set_text_size(width, m_line_height);

    m_send_button->set_rect(m_rect.x + width, pos_y, send_width, m_line_height);

    m_send_button->update_layout(screen, m_font);

    /* Creating console background */
    SDL_Surface* tmp_surf = SDL_CreateRGBSurface(0, m_rect.w, m_rect.h, 32, 0, 0, 0, 0);
    m_background_texture = SDL_CreateTextureFromSurface(screen->get_renderer(), tmp_surf);
    SDL_FreeSurface(tmp_surf);
    SDL_SetTextureBlendMode(m_background_texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(m_background_texture, m_alpha);
}

int Console::draw(Screen* screen){
    SDL_RenderCopy(screen->get_renderer(), m_background_texture, nullptr, &m_rect);

    int start = m_history.size()>static_cast<long unsigned int>(m_nb_visible_lines)?static_cast<int>(m_history.size())-m_nb_visible_lines:0;
    for(int x=start;x<static_cast<int>(m_history.size());x++){
        m_history[static_cast<long unsigned int>(x)]->draw(screen);//draw_offset_y(screen, x*30);
    }
    m_input->draw(screen);
    m_send_button->draw(screen);
    return 0;
}

int Console::update(SDL_Event* event, Screen* screen){
    if(m_input->update(event, screen) == 1 || m_send_button->update(event, screen) == 1){
        if(!m_input->is_empty()){
            create_entry(screen);
            m_input->flush(screen);
        }
    }
    return 0;
}

int Console::update_layout(Screen* screen){
    if(m_font == nullptr){
        std::cout << "Error updating console layout : Font has not been loaded" << std::endl;
        return 1;
    }
    m_input->update_image(screen);
    return m_send_button->update_layout(screen, m_font);
}

void Console::init_send_button(){
    m_send_button->set_text("->");
    m_send_button->set_rect(0, 0, 120, 20);
    m_send_button->set_background_color(255, 255, 255);
    m_send_button->set_contour_color(0, 0, 0);
    m_send_button->set_text_color(0, 0, 0);
    m_send_button->set_text_pos("CENTER");
}

void Console::create_entry(Screen* screen){
    int max = static_cast<int>(m_history.size())<m_nb_visible_lines?static_cast<int>(m_history.size()):m_nb_visible_lines;
    for(int x=0;x<max;x++)
        m_history[static_cast<long unsigned int>(x)]->move(0, -m_line_height);

    Button* tmp_button = new Button();
    tmp_button->set_rect(m_rect.x, m_rect.y + m_line_height*(m_nb_visible_lines-1), m_rect.w, m_line_height);
    tmp_button->set_text(m_input->get_text());
    tmp_button->set_text_pos("MID_LEFT");
    tmp_button->set_contour_color(0, 0, 0);
    tmp_button->set_background_color(0, 0, 0, 0);
    tmp_button->set_text_color(255, 255, 255, 255);
    tmp_button->update_layout(screen, m_font);
    m_history.push_back(tmp_button);
}
