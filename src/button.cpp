#include <iostream>
#include "../includes/button.h"

//Constructors
Button::Button()
:m_rect(new SDL_Rect),
m_text_rect(new SDL_Rect),
m_absolute_text_position(new SDL_Rect),
m_text_offset(new SDL_Rect),
m_text_position(4),
m_hover(false),
m_background_color({0, 0, 0, 0}),
m_foreground_color({255, 255, 255, 0}),
m_contour_color({255, 255, 255, 0}),
m_background_texture(nullptr),
m_foreground_texture(nullptr),
m_text(""),
m_pos_as_text(true),
m_font(nullptr)
{
    // The offset should be default 0
    m_text_offset->x = 0;
    m_text_offset->y = 0;
}

Button::~Button(){
    delete m_rect;
    SDL_DestroyTexture(m_background_texture);
    SDL_DestroyTexture(m_foreground_texture);
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

    m_text_rect->x = rect.x;
    m_text_rect->y = rect.y;
}

void Button::set_rect(int x, int y, int w, int h){
    m_rect->x = x;
    m_rect->y = y;
    m_rect->w = w;
    m_rect->h = h;

    m_text_rect->x = x;
    m_text_rect->y = y;
}

void Button::set_position(SDL_Rect rect){
    m_rect->x = rect.x;
    m_rect->y = rect.y;

    m_text_rect->x = rect.x;
    m_text_rect->y = rect.y;
}

void Button::set_position(int x, int y){
    m_rect->x = x;
    m_rect->y = y;

    m_text_rect->x = x;
    m_text_rect->y = y;
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

void Button::set_text_color(int r, int g, int b, int a){
    m_foreground_color = {
        static_cast<Uint8>(r),
        static_cast<Uint8>(g),
        static_cast<Uint8>(b),
        static_cast<Uint8>(a)

    };
}

void Button::set_background_color(int r, int g, int b, int a){
    m_background_color = {
        static_cast<Uint8>(r),
        static_cast<Uint8>(g),
        static_cast<Uint8>(b),
        static_cast<Uint8>(a)
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

void Button::move(int off_x, int off_y){
    m_rect->x += off_x;
    m_rect->y += off_y;

    m_text_rect->x += off_x;
    m_text_rect->y += off_y;
}

void Button::set_text_offset(int off_x, int off_y){
    if(m_pos_as_text){ // Offset is used only with relative positioning
        m_text_offset->x += off_x;
        m_text_offset->y += off_y;
    }
}

void Button::resize(int off_w, int off_h){
    m_rect->x += off_w;
    m_rect->y += off_h;
}

//Others

int Button::draw(Screen* screen){
    screen->blit(m_background_texture, NULL, *m_rect);
    screen->blit(m_foreground_texture, NULL, *m_text_rect);
    return 0;
}


int Button::update_layout(Screen* screen, TTF_Font* font){
    m_font = font;
    SDL_Surface* tmp_image = SDL_CreateRGBSurface(0, m_rect->w, m_rect->h, 32, 0, 0, 0, 0);

    SDL_Surface* tmp_text;

    if(m_hover){
        SDL_FillRect(
            tmp_image, NULL,
            SDL_MapRGB(
                tmp_image->format,
                m_foreground_color.r,
                m_foreground_color.g,
                m_foreground_color.b
            )
        );
        tmp_text = TTF_RenderText_Blended(
            font,
            m_text.c_str(),
            m_background_color
        );
    }
    else{
        SDL_FillRect(
            tmp_image, NULL,
            SDL_MapRGB(
                tmp_image->format,
                m_background_color.r,
                m_background_color.g,
                m_background_color.b
            )
        );
        tmp_text = TTF_RenderText_Blended(
            font,
            m_text.c_str(),
            m_foreground_color
        );
    }

    SDL_Rect position_offset = get_text_position(tmp_text);
    m_text_rect->x = m_rect->x + position_offset.x + m_text_offset->x;
    m_text_rect->y = m_rect->y + position_offset.y + m_text_offset->y;
    m_text_rect->w = tmp_text->w;
    m_text_rect->h = tmp_text->h;

    /*if(SDL_BlitSurface(tmp_text, NULL, tmp_image, &position) == -1)
        std::cout << "Error : " << SDL_GetError() << std::endl;
    */

    if(draw_contour(tmp_image, m_contour_color) != 0) std::cout << "Error while drawing contour : " << SDL_GetError() << std::endl;

    m_background_texture = screen->convert_surface_to_texure(tmp_image);
    if(m_background_color.a != 255){
        SDL_SetTextureBlendMode(m_background_texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(m_background_texture, m_background_color.a);
    }
    m_foreground_texture = screen->convert_surface_to_texure(tmp_text);
    if(m_foreground_color.a != 255){
        SDL_SetTextureBlendMode(m_foreground_texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(m_foreground_texture, m_foreground_color.a);
    }


    SDL_FreeSurface(tmp_text);
    SDL_FreeSurface(tmp_image);
    return 0;
}

int Button::draw_contour(SDL_Surface* surf, SDL_Color color){
    SDL_Surface* horizontal_line = SDL_CreateRGBSurface(0, surf->w, 1, 32, 0, 0, 0, 0);
    SDL_Surface* vertical_line = SDL_CreateRGBSurface(0, 1, surf->h, 32, 0, 0, 0, 0);
    SDL_FillRect(horizontal_line, NULL, SDL_MapRGB(surf->format, color.r, color.g, color.b));
    SDL_FillRect(vertical_line, NULL, SDL_MapRGB(surf->format, color.r, color.g, color.b));

    SDL_Rect position = {0, 0, 0, 0};
    SDL_BlitSurface(horizontal_line, NULL, surf, &position);
    SDL_BlitSurface(vertical_line, NULL, surf, &position);

    position = {surf->w-1, 0, 0, 0};
    SDL_BlitSurface(vertical_line, NULL, surf, &position);

    position = {0, surf->h-1, 0, 0};
    SDL_BlitSurface(horizontal_line, NULL, surf, &position);

    SDL_FreeSurface(horizontal_line);
    SDL_FreeSurface(vertical_line);

    return 0;
}

int Button::update(SDL_Event* event, Screen* screen){

    bool prev_hov = m_hover;
    switch(event->type){
        case SDL_MOUSEMOTION:
            if(collide(screen->get_mouse_pos()))
                m_hover = true;
            else
                m_hover = false;

            if(prev_hov != m_hover)
                update_layout(screen, m_font);
            break;
        case SDL_MOUSEBUTTONUP:
            if(collide({event->button.x, event->button.y, 0, 0}))
                return 1; //Button was clicked
            break;
        default:
            break;
    }

    return 0; //Nothing hapenned
}

bool Button::collide(SDL_Rect rect) const{
    if(rect.x > m_rect->x && rect.x < m_rect->x + m_rect->w)
        if(rect.y > m_rect->y && rect.y < m_rect->y + m_rect->h)
            return true;
    return false;
}
