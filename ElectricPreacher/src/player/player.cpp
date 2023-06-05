#include <iostream>

#include "player/player.hpp"

#include <core/log.hpp>
#include <core/screen.hpp>

Player::Player()
:m_position({0, 0, 32, 32}),
m_draw_position(m_position),
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
/**
 * @brief Initializes the player, loading the texture
 * 
 * @param sc The screen to load the texture from
 */
void Player::init(MiniEngine::Screen* sc){
    m_texture = sc->LoadTexture("assets/images/player.png");
    if(m_texture == nullptr) std::cout << "Error :" << SDL_GetError() << std::endl;
}

/**
 * @brief Handles the events of the player
 * 
 * @param event The event to handle
 */
bool Player::OnEvent(SDL_Event* event){
    if(m_status != STATUS::IDLE) return false;
    if(event->type != SDL_KEYDOWN) return false;

    switch(event->key.keysym.sym){
        case SDLK_w:
            ME_INFO("Player moving up");
            return move(SDLK_w);
        case SDLK_a:
            ME_INFO("Player moving left");
            return move(SDLK_a);
        case SDLK_s:
            ME_INFO("Player moving down");
            return move(SDLK_s);
        case SDLK_d:
            ME_INFO("Player moving right");
            return move(SDLK_d);
        default:
            return false;
    }
}

/**
 * @brief Updates the drawing position of the player
 * 
 * @param time_elapsed The time elapsed since the last frame
 */
void Player::OnUpdate(int time_elapsed){
    if(m_status == STATUS::WALKING){  // Run the walking "animation"
        m_walking_offset += (float)((double)m_speed * (double)time_elapsed / 1000.0);
        if(m_walking_offset >= 32.0){
            m_walking_offset = 0;
            update_position();
            m_status = STATUS::IDLE;
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
 */
void Player::OnRender(MiniEngine::Screen* sc) {
    m_draw_position = {m_position.x * 32, m_position.y * 32, 32, 32};
    if(m_status == STATUS::WALKING){
        switch(m_dir){
            case DIR::UP:
                m_draw_position.y -= (int)m_walking_offset;
                break;
            case DIR::DOWN:
                m_draw_position.y += (int)m_walking_offset;
                break;
            case DIR::LEFT:
                m_draw_position.x -= (int)m_walking_offset;
                break;
            case DIR::RIGHT:
                m_draw_position.x += (int)m_walking_offset;
                break;
            default:
                break;
        }
    }

    SDL_RenderCopy(sc->get_renderer(), m_texture, nullptr, &m_draw_position);
}

/**
 * @brief Sets the player status as moving and its direction according to the key pressed
 * 
 * @param sym The Keycode of the key pressed
 */
bool Player::move(SDL_Keycode sym){
    switch(sym){
        case SDLK_w:
            m_status = STATUS::WALKING;
            m_dir = DIR::UP;
            break;
        case SDLK_a:
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
            return false;
    }
    ME_INFO("Player status set to walking");
    return true;
}
