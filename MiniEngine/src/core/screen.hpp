#pragma once

#include <iostream>
#include <map>

#include <SDL.h>
#include <SDL_ttf.h>

#include "core/core.hpp"

/**
 * @brief The Screen class is a singleton that handles the window and the renderer of the game
 * It is responsible for handling some basic event and drawing functions
 */
namespace MiniEngine {
    struct WindowProps {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string& title = "MiniEngine",
            unsigned int width = 1280,
            unsigned int height = 720)
            : title(title), width(width), height(height)
        {
        }
    };

    class ME_API Screen {
        protected:
            // Avoid direct instantiation
            explicit Screen(const WindowProps& props);

        public:
            // Constructors
            virtual ~Screen();

            // Override
            Screen(Screen& other) = delete;
            void operator=(const Screen&) = delete;

            // Singleton pattern
            static Screen* Create(const WindowProps& props = WindowProps());

            // Getters
            int get_width() const;
            int get_height() const;
            int get_time_elapsed() const;

            bool is_running() const;
            bool get_key(SDL_Keycode) const;

            std::string get_caption() const;

            std::map<std::string, TTF_Font*> get_fonts() const;
            TTF_Font* get_font(std::string ID) const;
            SDL_Rect get_mouse_pos() const;
            SDL_Window* get_window() const;
            SDL_Renderer* get_renderer() const;
            SDL_Color get_background_color() const;

            // Setters
            void set_width(int);
            void set_height(int);
            void set_background_color(SDL_Color);
            void set_background_color(Uint8, Uint8, Uint8);
            void set_default_font(std::string font_id);
            void set_caption(std::string);
            void toggle_fps_show();
            void set_running(bool running);

            // Others
            int init();
            int build_window();
            int add_font(std::string font_path, int size, std::string font_id = "");
            SDL_Surface* load_image(std::string);
            SDL_Texture* load_texture(std::string);
            SDL_Texture* convert_surface_to_texure(SDL_Surface*) const;
            SDL_Surface* render_text_blend(std::string);
            SDL_Surface* render_text_blend(std::string, TTF_Font*, SDL_Color color = { 255, 255, 255, 255 });
            SDL_Surface* render_text_solid(std::string);
            SDL_Surface* render_text_solid(std::string, TTF_Font*, SDL_Color color = { 255, 255, 255, 255 });

            void handle_events(SDL_Event*);
            void update_screen();

            void compute_fps();

        private:
            int m_width;
            int m_height;
            int m_tile_size;

            Uint32 m_start_time;
            Uint32 m_time_elapsed;
            Uint32 m_time_since_last_fps_update;
            Uint32 m_fps;

            bool m_running;
            bool m_showing_fps;

            std::string m_window_caption;
            std::map<SDL_Keycode, bool> m_keyConf;

            SDL_Texture* m_fps_texture;
            SDL_Surface* m_fps_surface;
            SDL_Window* m_window;
            SDL_Renderer* m_Renderer;

            SDL_Color m_font_color;
            SDL_Color m_background_color;
            std::string m_default_font;
            std::map<std::string, TTF_Font*> m_fonts;

            SDL_Rect m_mouse_pos;
            SDL_Rect m_fps_pos;
    };
}