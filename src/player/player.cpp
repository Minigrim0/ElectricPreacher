#include <iostream>

#include "player/player.hpp"

Player::Player()
:m_position({0, 0, 32, 32}),
m_walking_offset(0),
m_texture(nullptr),
m_speed(16),
m_status(STATUS::IDLE),
m_dir(DIR::DOWN)
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

void Player::handle_event(SDL_Event* event){
    if(m_status != STATUS::IDLE) return;

    switch(event->type){
        case SDL_KEYDOWN:
            move(event);
            std::cout << "Move" << std::endl;
            break;
        case SDL_KEYUP:
            //move(event);
            break;
        default:
            break;
    }
}

void Player::update(Screen* sc){
    std::cout << m_walking_offset << std::endl;
    switch(m_status){
        case STATUS::IDLE:
            break;
        case STATUS::WALKING:
            m_walking_offset += m_speed * sc->get_time_elapsed() / 1000;
            if(m_walking_offset >= 32.0){
                m_walking_offset = 0;
                m_status = STATUS::IDLE;
            }
            break;
        case STATUS::ATTACKING:
            break;
        case STATUS::DEAD:
            break;
        default:
            break;
    }
}

/**
 * @brief Draws the player on screen
 * 
 * @param sc The screen to draw the player on
 * @return int 
 */
int Player::draw(Screen* sc) const{
    if(m_status == STATUS::WALKING){
        SDL_Rect dst = m_position;
        switch(m_dir){
            case DIR::UP:
                dst.y -= m_walking_offset;
                break;
            case DIR::DOWN:
                dst.y += m_walking_offset;
                break;
            case DIR::LEFT:
                dst.x -= m_walking_offset;
                break;
            case DIR::RIGHT:
                dst.x += m_walking_offset;
                break;
            default:
                break;
        }
        return SDL_RenderCopy(sc->get_renderer(), m_texture, nullptr, &dst);
    } else {
        return SDL_RenderCopy(sc->get_renderer(), m_texture, nullptr, &m_position);
    }
}


void Player::move(SDL_Event* event){
    switch(event->key.keysym.sym){
        case SDLK_z:
            m_status = STATUS::WALKING;
            m_dir = DIR::UP;
            break;
        case SDLK_q:
            m_status = STATUS::WALKING;
            m_dir = DIR::LEFT;
            break;
        case SDLK_s:
            m_status = STATUS::WALKING;
            m_dir = DIR::DOWN;
            break;
        case SDLK_d:
            m_status = STATUS::WALKING;
            m_dir = DIR::RIGHT;
            break;
        default:
            std::cout << "unhandled case" << std::endl;
    }
}
