#include "scenes/scene.hpp"

#include <core/log.hpp>

AbstractScene::AbstractScene(MiniEngine::Application *app, const std::string name)
    : m_scene(new MiniEngine::Scene(name)) {
    ME_INFO("Scene '{0}' created", name);
    app->add_scene(m_scene);
}

AbstractScene::~AbstractScene() { ME_INFO("Scene '{0}' destroyed", m_scene->get_name()); }

void AbstractScene::start(MiniEngine::Application *app) {
    ME_CORE_INFO("Starting scene '{0}'", m_scene->get_name());
    app->set_active_scene(m_scene);
}
