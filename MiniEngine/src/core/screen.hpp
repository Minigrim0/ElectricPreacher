#pragma once

#include <map>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

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

    class Screen {
        protected:
            // Avoid direct instantiation
            explicit Screen(const WindowProps& props);

        public:
            // Constructors
            virtual ~Screen();

            // Override
            Screen(Screen& other) = delete;
            void operator=(const Screen&) = delete;

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
            void SetWidth(int);
            void SetHeight(int);
            void SetBackgroundColor(SDL_Color);
            void SetBackgroundColor(Uint8, Uint8, Uint8);
            void SetDefaultFont(std::string font_id);
            void SetCaption(std::string);
            void SetRunning(bool running);

            // Others
            int Init();
            int BuildWindow();
            int AddFont(std::string font_path, int size, std::string font_id = "");
            SDL_Surface* LoadImage(std::string) const;
            SDL_Texture* LoadTexture(std::string) const;
            SDL_Texture* Surf2Text(SDL_Surface*) const;
            SDL_Surface* render_text_blend(std::string);
            SDL_Surface* render_text_blend(std::string, TTF_Font*, SDL_Color color = { 255, 255, 255, 255 });
            SDL_Surface* render_text_solid(std::string);
            SDL_Surface* render_text_solid(std::string, TTF_Font*, SDL_Color color = { 255, 255, 255, 255 });

            bool OnEvent(SDL_Event*);
            void Update();

        private:
            void FPSDisplayToggle();
            void FPSCompute();
            void FPSRender();

            int m_width;
            int m_height;
            int m_tile_size;

            Uint32 m_start_time;
            Uint32 m_time_elapsed;
            Uint32 m_time_since_last_fps_update;
            Uint32 m_fps;

            bool m_showing_fps;

            std::string m_window_caption;
            std::map<SDL_Keycode, bool> m_keyConf;

            SDL_Texture* m_fps_texture;
            SDL_Surface* m_fps_surface;
            SDL_Window* m_window;
            SDL_Renderer* m_Renderer;

            SDL_Color m_font_color;
            SDL_Color m_background_color;
            std::map<std::string, TTF_Font*> m_fonts;

            SDL_Rect m_mouse_pos;
            SDL_Rect m_fps_pos;
    };
}
