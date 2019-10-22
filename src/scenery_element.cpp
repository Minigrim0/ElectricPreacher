#include "../includes/scenery_element.h"
#include "../includes/constants.h"

//Constructors
SceneryElement::SceneryElement() : MapElement(),
m_type(0)
{}

SceneryElement::~SceneryElement()
{}

//Getters
int SceneryElement::get_type() const{
    return m_type;
}

//Setters
void SceneryElement::set_type(int type){
    m_type = type;
}

//Others
