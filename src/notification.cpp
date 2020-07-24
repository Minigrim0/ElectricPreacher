#include "../includes/notification.h"
#include "../includes/constants.h"

//Constructors
Notification::Notification()
:m_content(""),
m_position({0, 0, 0, 0}),
m_progress_bar_color({0, 0, 0, 0}),
m_text_color({0, 0, 0, 0}),
m_background(nullptr),
m_text_texture(nullptr),
m_icon(nullptr),
m_total_lifetime(10000),
m_current_lifetime(0),
m_alpha(255)
{}

Notification::~Notification(){
    SDL_DestroyTexture(m_background);
    SDL_DestroyTexture(m_text_texture);
    SDL_DestroyTexture(m_progress_bar);
}


// Setters
void Notification::set_position(int x, int y){
    m_position.x = x;
    m_position.y = y;
}

void Notification::set_text(std::string text){
    m_content = text;
}

void Notification::set_icon(SDL_Texture* tex){
    m_icon = tex;
}

void Notification::set_width(int w){
    m_position.w = w;
}

// Getters
int Notification::get_height() const{
    return m_position.h;
}

bool Notification::is_alive() const{
    return m_current_lifetime<m_total_lifetime;
}

int Notification::draw(Screen*){
    return 0;
}

int Notification::update(SDL_Event*, Screen*){
    return 0;
}

void Notification::init(Screen* screen, TTF_Font* font){
    screenMutex.lock();
        SDL_Surface* tmp_text = screen->render_text_blend(m_content, font);
    screenMutex.unlock();

    //SDL_Surface* tmp_background = SDL_CreateRGBSurface(0, x, x, 32, 0, 0, 0, 0);
}
