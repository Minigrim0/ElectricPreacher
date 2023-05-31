#include "map/elements/ground_element.hpp"
#include "map/elements/elements.hpp"

#include <core/log.hpp>

GroundElement::GroundElement(SDL_Point position)
:MapElement(false, &MAP_ELEMENT::GROUND, position)
{}

void GroundElement::interact(Player* player){
    ME_INFO("GroundElement::interact: Ground element at position ({}, {}) has been interacted with", m_position.x, m_position.y);
}
