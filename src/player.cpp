#include <iostream>

#include "../includes/player.hpp"

Player::Player()
:m_position({0, 0, 0, 0})
{}

Player::~Player(){}

void Player::set_position(SDL_Rect position){
    m_position = position;
}

void Player::set_position(int x, int y){
    m_position.x = x;
    m_position.y = y;
}