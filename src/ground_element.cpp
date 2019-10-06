/**
    name : ground_element.cpp
    purpose : Contains the source code for the class GroundElement

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>

#include "../includes/ground_element.h"

//Constructors
GroundElement::GroundElement(){}

GroundElement::~GroundElement(){}

//Getters
std::string GroundElement::get_type() const{return m_type;}

//Setters
void GroundElement::set_type(std::string type){
    m_type = type;
}
