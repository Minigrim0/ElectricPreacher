#include "UI/console.hpp"

#include "core/log.hpp"

namespace MiniEngine
{
    namespace UI
    {
        Console::Console() : Console(0, 0, 0, 0) {}

        Console::Console(int x, int y) : Console(x, y, 0, 0) {}

        Console::Console(int x, int y, int w) : Console(x, y, w, w) {}

        Console::Console(int x, int y, int w, int h)
            : m_rect({x, y, w, h}),
              m_history(std::vector<Widgets::Button *>()),
              m_font(nullptr),
              m_background_texture(nullptr),
              m_input(new Widgets::TextInput),
              m_send_button(new Widgets::Button),
              m_nb_visible_lines(5),
              m_line_height(0),
              m_alpha(125)
        {
            init_send_button();
        }

        Console::Console(TTF_Font *font)
            : m_rect({0, 0, 0, 0}),
              m_history(std::vector<Widgets::Button *>()),
              m_input(new Widgets::TextInput),
              m_send_button(new Widgets::Button),
              m_font(font),
              m_background_texture(nullptr),
              m_nb_visible_lines(5),
              m_line_height(0),
              m_alpha(125)
        {
            m_input->set_font(font);
            init_send_button();
        }

        Console::~Console()
        {
            delete m_input;
            delete m_send_button;
        }

        // Setters
        void Console::set_position(int x, int y)
        {
            m_rect.x = x;
            m_rect.y = y;
        }

        void Console::set_size(int w, int h)
        {
            m_rect.w = w;
            m_rect.h = h;
        }

        int Console::set_font(TTF_Font *font)
        {
            m_font = font;
            return 0;
        }

        int Console::set_font(std::string font_path, int font_size)
        {
            m_font = TTF_OpenFont(font_path.c_str(), font_size);
            if (m_font == nullptr)
            {
                ME_CORE_ERROR("Error loading font {0} : {1}", font_path, TTF_GetError());
                return 1;
            }
            m_input->set_font(font_path, 70);
            return 0;
        }

        // Others
        void Console::init(Screen *screen)
        {
            if (!(m_rect.w && m_rect.h))
            {
                ME_CORE_ERROR("Error initializing the console, missing size !");
                return;
            }

            m_line_height = static_cast<int>(static_cast<float>(m_rect.w) * 0.1);
            m_nb_visible_lines = static_cast<int>(static_cast<float>(m_rect.h) / static_cast<float>(m_line_height)) - 1;

            int width = static_cast<int>(static_cast<float>(m_rect.w) * 0.9);
            int send_width = static_cast<int>(static_cast<float>(m_rect.w) * 0.1);

            int pos_y = m_rect.y + m_line_height * (m_nb_visible_lines);

            m_input->set_position(m_rect.x, pos_y);
            m_input->set_text_size(width, m_line_height);
            m_input->set_OnSubmit(std::bind(&Console::OnTextSubmit, this, std::placeholders::_1));

            m_send_button->set_rect(m_rect.x + width, pos_y, send_width, m_line_height);
            m_send_button->update_layout(m_font);
            m_send_button->set_callback(std::bind(&Console::OnSendButtonPressed, this));

            /* Creating console background */
            SDL_Surface *tmp_surf = SDL_CreateRGBSurface(0, m_rect.w, m_rect.h, 32, 0, 0, 0, 0);
            m_background_texture = SDL_CreateTextureFromSurface(screen->get_renderer(), tmp_surf);
            SDL_FreeSurface(tmp_surf);
            SDL_SetTextureBlendMode(m_background_texture, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(m_background_texture, m_alpha);
        }

        void Console::OnRender(Screen *screen)
        {
            SDL_RenderCopy(screen->get_renderer(), m_background_texture, nullptr, &m_rect);

            int start = m_history.size() > static_cast<long unsigned int>(m_nb_visible_lines) ? static_cast<int>(m_history.size()) - m_nb_visible_lines : 0;
            for (int x = start; x < static_cast<int>(m_history.size()); x++)
            {
                m_history[static_cast<long unsigned int>(x)]->OnRender(screen); // draw_offset_y(screen, x*30);
            }
            m_input->OnRender(screen);
            m_send_button->OnRender(screen);
        }

        bool Console::OnEvent(SDL_Event *event)
        {
            return m_input->OnEvent(event) || m_send_button->OnEvent(event);
        }

        void Console::OnUpdate(int time_elapsed)
        {
            m_input->OnUpdate(time_elapsed);
            m_send_button->OnUpdate(time_elapsed);
        }

        int Console::update_layout()
        {
            if (m_font == nullptr)
            {
                ME_CORE_ERROR("Error updating console layout : Font has not been loaded");
                return 1;
            }
            m_input->update_image();
            return m_send_button->update_layout(m_font);
        }

        void Console::init_send_button()
        {
            m_send_button->set_text("->");
            m_send_button->set_rect(0, 0, 120, 20);
            m_send_button->set_background_color(255, 255, 255);
            m_send_button->set_contour_color(0, 0, 0);
            m_send_button->set_text_color(0, 0, 0);
            m_send_button->set_text_pos("CENTER");
        }

        /**
         * @brief The send button has been pressed,
         * Get the text from the input to create an entry
         * and then flush the input
         */
        void Console::OnSendButtonPressed() {
            ME_CORE_INFO("Console> Send Button pressed");
            if(m_input->get_text() != "") {
                this->OnTextSubmit(m_input->get_text());
                m_input->flush();
            }
        }

        /**
         * @brief The return key has been pressed on the input,
         * Create an entry
         * 
         * @param text The text from the input
         */
        void Console::OnTextSubmit(std::string text) {
            ME_CORE_INFO("Console> Text submitted : {0}", text);

            int max = static_cast<int>(m_history.size()) < m_nb_visible_lines ? static_cast<int>(m_history.size()) : m_nb_visible_lines;
            for (int x = 0; x < max; x++)
                m_history[static_cast<long unsigned int>(x)]->move(0, -m_line_height);

            Widgets::Button *tmp_button = new Widgets::Button();
            tmp_button->set_rect(m_rect.x, m_rect.y + m_line_height * (m_nb_visible_lines - 1), m_rect.w, m_line_height);
            tmp_button->set_text(text);
            tmp_button->set_text_pos("MID_LEFT");
            tmp_button->set_contour_color(0, 0, 0);
            tmp_button->set_background_color(0, 0, 0, 0);
            tmp_button->set_text_color(255, 255, 255, 255);
            tmp_button->update_layout(m_font);
            m_history.push_back(tmp_button);
        }
    }
}
