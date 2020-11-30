#include <iostream>

#include "../includes/player.hpp"

Player::Player()
:m_position({0, 0, 32, 32})
{}

Player::~Player(){}

// Setters
void Player::set_position(SDL_Rect position){
    m_position = position;
}

void Player::set_position(int x, int y){
    m_position.x = x;
    m_position.y = y;
}

// Others
void Player::init(Screen* sc){
    m_texture = sc->load_texture("assets/images/player.png");
    if(m_texture == nullptr) std::cout << "Error :" << SDL_GetError() << std::endl;
}

void Player::update(SDL_Event* event){
    switch(event->type){
        case SDL_KEYDOWN:
            move(event);
            break;
        case SDL_KEYUP:
            //move(event);
            break;
        default:
            std::cout << "no keyboard action" << std::endl;
    }
}

int Player::draw(Screen* sc) const{
    return SDL_RenderCopy(sc->get_renderer(), m_texture, nullptr, &m_position);
}


void Player::move(SDL_Event* event){
    switch(event->key.keysym.sym){
        case SDLK_z:
            m_position.y -= 10;
            break;
        case SDLK_q:
            m_position.x -= 10;
            break;
        case SDLK_s:
            m_position.y += 10;
            break;
        case SDLK_d:
            m_position.x += 10;
            break;
        default:
            std::cout << "unhandled case" << std::endl;
    }
}