#include "event/layer.hpp"

#include "core/log.hpp"


namespace MiniEngine {
    namespace Event {
        Layer::Layer(uint8_t id)
        :m_interactibles(std::vector<Interactible*>()),
        m_id(id)
        {
            ME_CORE_INFO("Creating layer {0}", id);
        }

        Layer::~Layer() {
            for (auto interactible : m_interactibles) {
                delete interactible;
            }
        }

        void Layer::attach(Interactible* interactible) {
            ME_CORE_INFO("Attaching interactible to layer {0}", m_id);
            m_interactibles.push_back(interactible);
        }

        bool Layer::OnEvent(SDL_Event* event) {
            for (auto interactible : m_interactibles) {
                if (interactible->OnEvent(event)) {
                    ME_CORE_TRACE("Interactible on layer {0} handled event", m_id);
                    return true;
                }
            }
            return false;
        }

        void Layer::OnRender(Screen* screen) {
            for (auto interactible : m_interactibles) {
                interactible->OnRender(screen);
            }
        }

        void Layer::OnUpdate(int time_elapsed) {
            for (auto interactible : m_interactibles) {
                interactible->OnUpdate(time_elapsed);
            }
        }
    }
}
