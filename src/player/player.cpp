#include <iostream>

#include "player/player.hpp"

Player::Player()
:m_position({0, 0, 32, 32}),
m_walking_offset(0),
m_texture(nullptr),
m_speed(64),
m_status(STATUS::IDLE),
m_dir(DIR::DOWN)
{}

Player::~Player(){}

/**
 * @brief Sets the position of the player using a SDL_Rect
 * 
 * @param position The position (in tiles)
 */
void Player::set_position(SDL_Rect position){
    m_position = position;
}

/**
 * @brief Sets the position of the player using x and y coordinates
 * 
 * @param x The x coordinate (in tiles)
 * @param y The y coordinate (in tiles)
 */
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

    if(event->type == SDL_KEYDOWN)
        move(event->key.keysym.sym);
}

void Player::update(Screen* sc){
    switch(m_status){
        case STATUS::IDLE:
            if(sc->get_key(SDLK_z)) move(SDLK_z);
            else if(sc->get_key(SDLK_q)) move(SDLK_q);
            else if(sc->get_key(SDLK_s)) move(SDLK_s);
            else if(sc->get_key(SDLK_d)) move(SDLK_d);
            break;
        case STATUS::WALKING:
            m_walking_offset += m_speed * sc->get_time_elapsed() / 1000.0;
            if(m_walking_offset >= 32.0){
                m_walking_offset = 0;
                update_position();
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

    m_draw_position = {m_position.x * 32, m_position.y * 32, 32, 32};
    if(m_status == STATUS::WALKING){
        switch(m_dir){
            case DIR::UP:
                m_draw_position.y -= m_walking_offset;
                break;
            case DIR::DOWN:
                m_draw_position.y += m_walking_offset;
                break;
            case DIR::LEFT:
                m_draw_position.x -= m_walking_offset;
                break;
            case DIR::RIGHT:
                m_draw_position.x += m_walking_offset;
                break;
            default:
                break;
        }
    }
}

/**
 * @brief Updates the position of the player after the walking animation
 */
void Player::update_position(){
    switch(m_dir){
        case DIR::UP:
            m_position.y -= 1;
            break;
        case DIR::DOWN:
            m_position.y += 1;
            break;
        case DIR::LEFT:
            m_position.x -= 1;
            break;
        case DIR::RIGHT:
            m_position.x += 1;
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
    return SDL_RenderCopy(sc->get_renderer(), m_texture, nullptr, &m_draw_position);
}

/**
 * @brief Sets the player status as moving and its direction according to the key pressed
 * 
 * @param sym The Keycode of the key pressed
 */
void Player::move(SDL_Keycode sym){
    switch(sym){
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
