#include "core/scene.hpp"

#include "core/log.hpp"

namespace MiniEngine {
Scene::Scene() : Scene("Default") {}

Scene::Scene(std::string name)
    : m_current(false), m_name(name), m_layer_manager(new Event::LayerManager) {
    ME_CORE_INFO("Creating scene {0}", name);
}

Scene::~Scene() {}

/**
 * @brief Get the running state of the Scene
 *
 * @return true The Scene is currently running
 * @return false The Scene is not running
 */
bool Scene::is_current() const { return m_current; }

/**
 * @brief Get the title of the Scene
 *
 * @return std::string The title of the Scene
 */
std::string Scene::get_name() const { return m_name; }

/**
 * @brief Set the running state of the Scene
 *
 * @param running Whether the Scene should be running or not
 */
void Scene::set_running(bool running) { m_current = running; }

/**
 * @brief Add a layer to the Scene
 *
 * @param index The index of the layer
 * @param layer The layer to add
 */
void Scene::add_layer(uint8_t index, Event::Layer *layer) { m_layer_manager->attach(index, layer); }

/**
 * @brief Add an interactible to the Scene
 *
 * @param index The index of the interactible
 * @param interactible The interactible to add
 */
void Scene::add_interactible(uint8_t index, Event::Interactible *interactible) {
    m_layer_manager->attach(index, interactible);
}

/**
 * @brief Updates the Scene, handles events
 *
 * @param event The event handler, used to get current event if any
 */
bool Scene::OnEvent(SDL_Event *event) { return m_layer_manager->OnEvent(event); }

/**
 * @brief Draws the Scene to the screen
 *
 * @param sc The screen on which to draw
 */
void Scene::OnRender(Screen *sc) { m_layer_manager->OnRender(sc); }

/**
 * @brief Updates the Scene
 *
 * @param time_elapsed The time elapsed since last update
 */
void Scene::OnUpdate(int time_elapsed) { m_layer_manager->OnUpdate(time_elapsed); }
} // namespace MiniEngine
