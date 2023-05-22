#include <SDL_events.h>
#include <SDL_mouse.h>
#include <fstream>
#include <SDL.h>

#include <nlohmann/json.hpp>

#include "core/log.hpp"
#include "core/scene.hpp"
#include "core/screen.hpp"

#include "UI/widgets/button.hpp"

namespace MiniEngine
{
    Scene::Scene()
    :Scene("Default")
    {}

    Scene::Scene(std::string name)
    :m_current(false),
    m_name(name),
    m_layer_manager(new Event::LayerManager),
    m_title(nullptr),
    m_buttons(std::vector<UI::Widgets::Button*>())
    {
		ME_CORE_INFO("Creating scene {0}", name);
	}

    Scene::~Scene() {}

    /**
     * @brief Get the running state of the Scene
     *
     * @return true The Scene is currently running
     * @return false The Scene is not running
     */
    bool Scene::is_current() const
    {
        return m_current;
    }

    /**
     * @brief Get the title of the Scene
     *
     * @return std::string The title of the Scene
     */
    std::string Scene::get_name() const
    {
        return m_name;
    }

    /**
     * @brief Set the running state of the Scene
     *
     * @param running Whether the Scene should be running or not
     */
    void Scene::set_running(bool running)
    {
        m_current = running;
    }

    /**
     * @brief Create a button that holds the title
     *
     * @param title The json description of the title
     */
    void Scene::set_title(nlohmann::json title, Screen *screen)
    {
        int off_x = title["offset"][0];
        int off_y = title["offset"][1];

        m_title = new UI::Widgets::Button;
        m_title->set_text(title["text"]);
        m_title->set_position(0, 0);

        m_title->set_size(screen->get_width(), screen->get_height());

        m_title->set_text_color(
            title["text-color"]["r"],
            title["text-color"]["g"],
            title["text-color"]["b"]);
        m_title->set_background_color(0, 0, 0, 0);
        if (title["text_position_type"] == "txt")
            m_title->set_text_pos(
                title["text-position"]);
        else
            m_title->set_text_pos(
                title["text-position_x"],
                title["text-position_y"]);

        m_title->set_text_offset(off_x, off_y);
        m_title->update_layout(screen->get_font(title["font_id"]));
    }

    /**
     * @brief Add an already created button to the list of buttons
     *
     * @param newButton The button to add
     */
    void Scene::add_button(UI::Widgets::Button *newButton)
    {
        m_buttons.push_back(newButton);
    }

    /**
     * @brief Add a collection of button from a parsed json list
     *
     * @param buttons The list of buttons to add
     * @return int 0 on success, -1 on error
     */
    int Scene::add_buttons(nlohmann::json buttons, Screen *screen)
    {
        for (unsigned int index = 0; index < buttons.size(); ++index)
        {
            m_buttons.push_back(new UI::Widgets::Button);

            m_buttons.back()->set_text(buttons[index]["name"]);

            m_buttons.back()->set_position(
                buttons[index]["position_x"],
                buttons[index]["position_y"]);

            m_buttons.back()->set_size(
                buttons[index]["size_x"],
                buttons[index]["size_y"]);

            m_buttons.back()->set_text_color(
                buttons[index]["text-color"]["r"],
                buttons[index]["text-color"]["g"],
                buttons[index]["text-color"]["b"]);

            m_buttons.back()->set_background_color(
                buttons[index]["background-color"]["r"],
                buttons[index]["background-color"]["g"],
                buttons[index]["background-color"]["b"]);

            m_buttons.back()->set_contour_color(
                buttons[index]["contour-color"]["r"],
                buttons[index]["contour-color"]["g"],
                buttons[index]["contour-color"]["b"]);

            // Set text-position, via text or absolute coordinates
            if (buttons[index]["text_position_type"] == "txt")
            {
                m_buttons.back()->set_text_pos(
                    buttons[index]["text-position"]);
            }
            else
            {
                m_buttons.back()->set_text_pos(
                    buttons[index]["text-position_x"],
                    buttons[index]["text-position_y"]);
            }

            m_buttons.back()->set_action_type(buttons[index]["action_type"], buttons[index]["action_operand"]);

            // Finally update the button image
            m_buttons.back()->update_layout(screen->get_font(buttons[index]["font_id"]));
        }
        return 0;
    }

    /**
     * @brief Add a layer to the Scene
     *
     * @param index The index of the layer
     * @param layer The layer to add
     */
    void Scene::add_layer(uint8_t index, Event::Layer *layer)
    {
        m_layer_manager->attach(index, layer);
    }

    /**
     * @brief Add an interactible to the Scene
     *
     * @param index The index of the interactible
     * @param interactible The interactible to add
     */
    void Scene::add_interactible(uint8_t index, Event::Interactible* interactible) {
		m_layer_manager->attach(index, interactible);
	}

    /**
     * @brief Updates the Scene, handles events
     *
     * @param event The event handler, used to get current event if any
     */
    bool Scene::OnEvent(SDL_Event *event) {
        return m_layer_manager->OnEvent(event);
    }

    /**
     * @brief Draws the Scene to the screen
     *
     * @param sc The screen on which to draw
     */
    void Scene::OnRender(Screen *sc) {
        m_layer_manager->OnRender(sc);
    }

    /**
     * @brief Updates the Scene
     *
     * @param time_elapsed The time elapsed since last update
     */
    void Scene::OnUpdate(int time_elapsed) {
        m_layer_manager->OnUpdate(time_elapsed);
    }

    /**
     * @brief Create a Scene from a JSON file
     *
     * @param screen The screen on which to draw
     * @param JSONsource The path to the JSON file
     * @return 0 on success, -1 on error
     */
    int Scene::createfrom(std::string JSONsource, Screen *screen) {
        std::ifstream json_in(JSONsource.c_str());
        nlohmann::json root;
        json_in >> root;

        // Setup Scene-wide informations
        m_name = root["Scene_name"];
        screen->add_font(root["font_path"], root["font_size"], root["font_id"]);

        // Setup Buttons
        const nlohmann::json buttons = root["Buttons"];
        this->add_buttons(buttons, screen);

        // Setup title
        const nlohmann::json title = root["Title"];
        this->set_title(title, screen);

        json_in.close();
        return 0;
    }
}
