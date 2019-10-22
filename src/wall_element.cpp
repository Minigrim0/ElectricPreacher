/**
    name : wall_element.cpp
    purpose : Contains the source code for the wall element class
*/

#include "../includes/wall_element.h"

WallElement::WallElement() : MapElement(),
m_is_trap(false),
m_breakable(false),
m_transparent(false)
{}

WallElement::~WallElement(){}
