#include <iostream>
#include "../includes/button.h"

//Constructors
Button::Button()
:m_rect(new SDL_Rect),
m_absolute_text_position(new SDL_Rect),
m_text_position(4),
m_hover(false),
m_background_color({0, 0, 0, 0}),
m_foreground_color({255, 255, 255, 0}),
m_contour_color({255, 255, 255, 0}),
m_image(nullptr),
m_text(""),
m_pos_as_text(true),
m_font(nullptr)
{}

Button::Button(const Button& button)
:m_rect(new SDL_Rect),
m_absolute_text_position(new SDL_Rect),
m_text_position(4),
m_hover(false),
m_background_color(button.get_background_color()),
m_foreground_color(button.get_foreground_color()),
m_contour_color(button.get_contour_color()),
m_image(nullptr),
m_text(button.get_text()),
m_pos_as_text(true),
m_font(nullptr)
{
    *m_rect = button.get_rect();
}

Button::~Button(){
    delete m_rect;
    SDL_FreeSurface(m_image);
}

//Operators
Button& Button::operator=(const Button& button){
    m_background_color = button.get_background_color();
    m_foreground_color = button.get_foreground_color();
    m_text = button.get_text();
    *m_rect = button.get_rect();

    return *this;
}

//Getters
SDL_Rect Button::get_rect() const{
    return *m_rect;
}

SDL_Color Button::get_background_color() const{
    return m_background_color;
}

SDL_Color Button::get_foreground_color() const{
    return m_foreground_color;
}

SDL_Color Button::get_contour_color() const{
    return m_contour_color;
}

SDL_Rect Button::get_text_position(SDL_Surface* tmp_text) const{
    SDL_Rect position;
    if(m_pos_as_text){
        switch(m_text_position){
            case 0:
                position.x = 0;
                position.y = 0;
                break;
            case 1:
                position.x = (m_rect->w - tmp_text->w)/2;
                position.y = 0;
                break;
            case 2:
                position.x = m_rect->w - tmp_text->w;
                position.y = 0;
                break;
            case 3:
                position.x = 0;
                position.y = (m_rect->h - tmp_text->h)/2;
                break;
            case 4:
                position.x = (m_rect->w - tmp_text->w)/2;
                position.y = (m_rect->h - tmp_text->h)/2;
                break;
            case 5:
                position.x = m_rect->w - tmp_text->w;
                position.y = (m_rect->h - tmp_text->h)/2;
                break;
            case 6:
                position.x = 0;
                position.y = m_rect->h - tmp_text->h;
                break;
            case 7:
                position.x = (m_rect->w - tmp_text->w)/2;
                position.y = m_rect->h - tmp_text->h;
                break;
            case 8:
                position.x = m_rect->w - tmp_text->w;
                position.y = m_rect->h - tmp_text->h;
                break;
            default:
                position.x = 0;
                position.y = 0;
        }
    }
    return position;
}

std::string Button::get_text() const{
    return m_text;
}

//Setters
void Button::set_rect(SDL_Rect rect){
    *m_rect = rect;
}

void Button::set_rect(int x, int y, int w, int h){
    m_rect->x = x;
    m_rect->y = y;
    m_rect->w = w;
    m_rect->h = h;
}

void Button::set_position(SDL_Rect rect){
    m_rect->x = rect.x;
    m_rect->y = rect.y;
}

void Button::set_position(int x, int y){
    m_rect->x = x;
    m_rect->y = y;
}

void Button::set_text_pos(std::string position){
    m_pos_as_text = true;

    std::string arr[9] = {
        "TOP_LEFT", "TOP_CENTER", "TOP_RIGHT",
        "MID_LEFT", "MID_CENTER", "MID_RIGHT",
        "BOT_LEFT", "BOT_CENTER", "BOT_RIGHT"
    };
    for(int x=0;x<9;x++)
        if(position == arr[x])
            m_text_position = x;
}

void Button::set_text_pos(int x, int y){
    m_pos_as_text = false;
    m_absolute_text_position->x = x;
    m_absolute_text_position->y = y;
}

void Button::set_text_color(int r, int g, int b){
    m_foreground_color = {
        static_cast<Uint8>(r),
        static_cast<Uint8>(g),
        static_cast<Uint8>(b),
        0
    };
}

void Button::set_background_color(int r, int g, int b){
    m_background_color = {
        static_cast<Uint8>(r),
        static_cast<Uint8>(g),
        static_cast<Uint8>(b),
        0
    };
}

void Button::set_contour_color(int r, int g, int b){
    m_contour_color = {
        static_cast<Uint8>(r),
        static_cast<Uint8>(g),
        static_cast<Uint8>(b),
        0
    };
}

void Button::set_size(SDL_Rect rect){
    m_rect->w = rect.w;
    m_rect->h = rect.h;
}

void Button::set_size(int w, int h){
    m_rect->w = w;
    m_rect->h = h;
}

void Button::set_text(std::string text){
    m_text = text;
}

//Others
int Button::update_layout(Screen* screen, TTF_Font* font){
    m_font = font;
    m_image = SDL_CreateRGBSurface(0, m_rect->w, m_rect->h, 32, 0, 0, 0, 0);
    if(m_hover)
        SDL_FillRect(
            m_image, NULL,
            SDL_MapRGB(
                screen->get_format(),
                m_contour_color.r,
                m_contour_color.g,
                m_contour_color.b
            )
        );
    else
        SDL_FillRect(
            m_image, NULL,
            SDL_MapRGB(
                screen->get_format(),
                m_background_color.r,
                m_background_color.g,
                m_background_color.b
            )
        );

    SDL_Surface* tmp_text = TTF_RenderText_Blended(
        font,
        m_text.c_str(),
        m_foreground_color
    );
    SDL_Rect position = get_text_position(tmp_text);

    if(SDL_BlitSurface(tmp_text, NULL, m_image, &position) == -1)
        std::cout << "Error : " << SDL_GetError() << std::endl;

    if(draw_contour(screen, m_contour_color) != 0) std::cout << "Error while drawing contour : " << SDL_GetError() << std::endl;

    SDL_FreeSurface(tmp_text);
    return 0;
}

int Button::draw_contour(Screen* screen, SDL_Color color){
    SDL_Surface* horizontal_line = SDL_CreateRGBSurface(0, m_image->w, 1, 32, 0, 0, 0, 0);
    SDL_Surface* vertical_line = SDL_CreateRGBSurface(0, 1, m_image->h, 32, 0, 0, 0, 0);
    SDL_FillRect(horizontal_line, NULL, SDL_MapRGB(screen->get_format(), color.r, color.g, color.b));
    SDL_FillRect(vertical_line, NULL, SDL_MapRGB(screen->get_format(), color.r, color.g, color.b));

    SDL_Rect position = {0, 0, 0, 0};
    SDL_BlitSurface(horizontal_line, NULL, m_image, &position);
    SDL_BlitSurface(vertical_line, NULL, m_image, &position);

    position = {m_image->w-1, 0, 0, 0};
    SDL_BlitSurface(vertical_line, NULL, m_image, &position);

    position = {0, m_image->h-1, 0, 0};
    SDL_BlitSurface(horizontal_line, NULL, m_image, &position);

    SDL_FreeSurface(horizontal_line);
    SDL_FreeSurface(vertical_line);

    return 0;
}

int Button::draw(Screen* screen){
    return screen->blit_surface(m_image, NULL, *m_rect);
}

void Button::update(Screen* screen){
    bool prev_hov = m_hover;
    if(collide(screen->get_mouse_pos()))
        m_hover = true;
    else
        m_hover = false;

    if(prev_hov != m_hover)
        update_layout(screen, m_font);
}

bool Button::collide(SDL_Rect rect) const{
    if(rect.x > m_rect->x && rect.x < m_rect->x + m_rect->w)
        if(rect.y > m_rect->y && rect.y < m_rect->y + m_rect->h)
            return true;
    return false;

}
