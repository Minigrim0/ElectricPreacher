#include "application.hpp"

#include "core/log.hpp"

namespace MiniEngine {
    Application::Application():m_project_name("MiniEngine Application") {}
    Application::Application(std::string project_name):m_project_name(project_name) {
		ME_CORE_INFO("Application {0} created!", project_name);
	}

    Application::~Application(){}

    void Application::Run(){
        ME_CORE_INFO("Starting the application");
		m_screen = std::unique_ptr<Screen>(Screen::Create());
		m_screen->set_width(1920);
		m_screen->set_height(1080);
		m_screen->set_caption(
			"The Electric Preacher (" +
			std::to_string(0) + "." +
			std::to_string(1) + "." +
			std::to_string(2) + ")");
		m_screen->init();

        while (true);
    }
}