#include "event/layer.hpp"

#include "core/log.hpp"


namespace MiniEngine {
    namespace Event {
        Layer::Layer(uint16_t id)
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
            ME_CORE_INFO("Layer {0} handling event {1}", m_id, event->type);
            for (auto interactible : m_interactibles) {
                if (interactible->OnEvent(event)) {
                    return true;
                }
            }
            return false;
        }
    }
}
