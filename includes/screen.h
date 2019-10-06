#ifndef screen_h
    #define screen_h

/**
    name : screen.h
    purpose : Contains prototypes for the Screen class

    @author : minigrim0
    @version : 1.1
*/

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
    Class : Screen
    purpose : Handle all the screen/window related things, such as creating it,
        naming it, loading images,...
*/
class Screen{
    public:
        //Constructors
        Screen();
        Screen(const Screen&);
        ~Screen();

        //Override
        Screen& operator=(const Screen&);

        //Getters
        int get_height() const;
        int get_width() const;
        SDL_Window *get_window() const;
        SDL_Surface *get_surface() const;
        TTF_Font* get_font() const;
        bool is_running() const;

        //Setters
        int set_height(int);
        int set_width(int);
        int set_current_surface(SDL_Surface*);
        void set_caption(std::string);
        void toggle_fps_show();

        //Others
        int init();
        int build_window();
        SDL_Surface *load_image(std::string);
        int blit_surface(const SDL_Rect*, int, int);
        int blit_surface(const SDL_Rect*, SDL_Rect);

        void handle_events();
        void update_screen();

    private:
        int m_width;
        int m_height;
        Uint32 m_start_time;
        Uint32 m_time_elapsed;

        bool m_running;
        bool m_showing_fps;

        std::string m_window_caption;

        SDL_Surface *m_screen_surface;
        SDL_Surface *m_current_surface;
        SDL_Window *m_window;

        SDL_Event m_event_handler;

        SDL_Color m_font_color;
        TTF_Font* m_font;
};

#endif
