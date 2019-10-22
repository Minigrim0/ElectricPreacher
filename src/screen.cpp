/**
    name : screen.cpp
    purpose : Contains source code of the screen class

    @author : minigrim0
    @version : 1.3
*/

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../includes/screen.h"
#include "../includes/constants.h"

//Constructors
Screen::Screen()
:m_window(nullptr),
m_screen_surface(nullptr),
m_font(nullptr),
m_running(false),
m_showing_fps(false),
m_height(640),
m_width(480),
m_window_caption("SDL Application"),
m_font_path("assets/fonts/courrier_new.ttf")
{
    m_font_color.r = (Uint8)255;
    m_font_color.g = (Uint8)255;
    m_font_color.b = (Uint8)255;

    m_background_color.r = (Uint8)0;
    m_background_color.g = (Uint8)0;
    m_background_color.b = (Uint8)0;
}

Screen::Screen(const Screen& screen)
:m_window(screen.get_window()),
m_screen_surface(screen.get_surface()),
m_width(screen.get_width()),
m_height(screen.get_height()),
m_font(screen.get_font())
{
    m_font_color.r = (Uint8)255;
    m_font_color.g = (Uint8)255;
    m_font_color.b = (Uint8)255;

    m_background_color.r = (Uint8)0;
    m_background_color.g = (Uint8)0;
    m_background_color.b = (Uint8)0;
}

Screen::~Screen(){
    SDL_DestroyWindow(m_window);
    TTF_CloseFont(m_font);
    TTF_Quit();
    SDL_Quit();
}

//Override
Screen& Screen::operator=(const Screen& screen){
    m_window = screen.get_window();
    m_screen_surface = screen.get_surface();
    m_width = screen.get_width();
    m_height = screen.get_height();
    m_font = screen.get_font();

    return *this;
}

//Getters
int Screen::get_height() const{return m_height;}
int Screen::get_width() const{return m_width;}
std::string Screen::get_caption() const{return m_window_caption;}
SDL_Window* Screen::get_window() const{return m_window;}
SDL_Surface* Screen::get_surface() const{return m_screen_surface;}
const SDL_PixelFormat* Screen::get_format() const{return m_screen_surface->format;}
SDL_Color Screen::get_background_color() const{return m_background_color;}
TTF_Font* Screen::get_font() const{return m_font;}
bool Screen::is_running() const{return m_running;}

//Setters
int Screen::set_height(int height){
    if(height <= 0)
        return 1;
    m_height = height;
    return 0;
}

int Screen::set_width(int width){
    if(width <= 0)
        return 1;
    m_width = width;
    return 0;
}

int Screen::set_current_surface(SDL_Surface* surf){
    if(surf == NULL) return 1;

    m_current_surface = surf;
    return 0;
}

void Screen::set_background_color(SDL_Color color){
    m_background_color = color;
}

void Screen::set_background_color(Uint8 r, Uint8 g, Uint8 b){
    m_background_color.r = r;
    m_background_color.g = g;
    m_background_color.b = b;
}

void Screen::set_font(std::string path){
    m_font_path = path;
}

void Screen::set_caption(std::string caption){
    m_window_caption = caption;
    SDL_SetWindowTitle(m_window, m_window_caption.c_str());
}

void Screen::toggle_fps_show(){
    m_showing_fps = !m_showing_fps;
}

//Others
int Screen::init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    return 0;
}

int Screen::build_window(){
    if(m_width <= 0 || m_height <= 0) return 1;

    m_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
    if(m_window == NULL){
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    m_screen_surface = SDL_GetWindowSurface(m_window);

    if(TTF_Init() == -1){
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
        return 1;
    }
    m_font = TTF_OpenFont(m_font_path.c_str(), 16);
    if(!m_font){
        std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
        return 1;
    }
    TTF_SetFontStyle(m_font, TTF_STYLE_BOLD);

    m_running = true;
    return 0;
}

SDL_Surface* Screen::load_image(std::string path){
    SDL_Surface *surf = NULL;
    surf = IMG_Load(path.c_str());
    if(surf == NULL)
        std::cout << "Error loading image " << SDL_GetError() << std::endl;

    return surf;
}

SDL_Surface* Screen::render_text_blend(std::string text){
    return TTF_RenderText_Blended(m_font, text.c_str(), m_font_color);
}

SDL_Surface* Screen::render_text_solid(std::string text){
    return TTF_RenderText_Solid(m_font, text.c_str(), m_font_color);
}

int Screen::blit_surface(SDL_Surface* surf, const SDL_Rect* src_rect, int x, int y){
    SDL_Rect dst_rect;
    dst_rect.x = x;
    dst_rect.y = y;
    return SDL_BlitSurface(
        surf, //Src image
        src_rect, //Src rect
        m_screen_surface, //Dest surf
        &dst_rect); //Dest rect
}

int Screen::blit_surface(SDL_Surface* surf, const SDL_Rect* src_rect, SDL_Rect position){
    return SDL_BlitSurface(
        surf, //Src image
        src_rect, //Src rect
        m_screen_surface, //Dest surf
        &position); //Dest rect
}

int Screen::blit_surface(const SDL_Rect* src_rect, int x, int y){
    SDL_Rect dst_rect;
    dst_rect.x = x;
    dst_rect.y = y;
    return SDL_BlitSurface(
        m_current_surface, //Src image
        src_rect, //Src rect
        m_screen_surface, //Dest surf
        &dst_rect); //Dest rect
}

int Screen::blit_surface(const SDL_Rect* src_rect, SDL_Rect position){
    return SDL_BlitSurface(
        m_current_surface, //Src image
        src_rect, //Src rect
        m_screen_surface, //Dest surf
        &position); //Dest rect
}

void Screen::handle_events(){
    while( SDL_PollEvent(&m_event_handler) != 0){
        if(m_event_handler.type == SDL_QUIT){
            m_running = false;
        }
        else if(m_event_handler.type == SDL_KEYUP){
            switch(m_event_handler.key.keysym.sym){
                case SDLK_F3:
                    toggle_fps_show();
                    break;
                default:
                    break;
            }
        }
    }
}

void Screen::update_screen(){
    m_time_elapsed = SDL_GetTicks() - m_start_time;
    m_start_time = SDL_GetTicks();
    m_time_since_last_fps_update += m_time_elapsed;
    if(m_showing_fps){
        compute_fps();
    }

    SDL_UpdateWindowSurface(m_window);
    SDL_FillRect(
        m_screen_surface,
        NULL,
        SDL_MapRGB(
            m_screen_surface->format,
            m_background_color.r,
            m_background_color.b,
            m_background_color.b
        )
    );
}

void Screen::compute_fps(){
    if(m_time_since_last_fps_update >= 1000){
        m_fps = (int)(1000.0/(double)m_time_elapsed);
        m_time_since_last_fps_update = 0;
    }

    SDL_Surface *tmp_image = NULL;
    std::string fps_text = std::to_string(m_fps) + " FPS";
    tmp_image = TTF_RenderText_Solid(m_font, fps_text.c_str(), m_font_color);
    set_current_surface(tmp_image);
    blit_surface(NULL, 15, 15);
    SDL_FreeSurface(tmp_image);
}
