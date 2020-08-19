#include "../includes/container.h"

Container::Container()
:m_rect({0, 0, 0, 0}),
m_widgets(std::vector<Widget*>())
{}

Container::~Container(){}
