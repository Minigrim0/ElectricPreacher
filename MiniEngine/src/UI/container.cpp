#include "UI/container.hpp"

namespace MiniEngine {
    namespace UI {
        Container::Container()
        :m_rect({0, 0, 0, 0}),
        m_widgets(std::vector<Event::Interactible*>()),
        type(0)
        {}

        Container::~Container(){}

        // Others
        void Container::OnRender(Screen* screen){
            return;
        }

        void Container::OnUpdate(int time_elapsed){
            return;
        }

        bool Container::OnEvent(SDL_Event* event){
            return false;
        }
    }
}
