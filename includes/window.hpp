#ifndef window_h
    #define window_h

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "../src/nlohmann/json.hpp"
#include "../src/UI/includes/button.hpp"
#include "../src/screen/includes/screen.hpp"

class Window{
    public:
        Window();
        virtual ~Window();

        //Getters
        bool is_running() const;
        std::string get_title() const;

        //Setters
        void set_running(bool);
        void set_title(Screen* screen, nlohmann::json title);
        int set_font(std::string path);

        //Others
        void add_button(Button* newButton);
        int add_button(Screen* screen, nlohmann::json buttons);
        void update(SDL_Event* event, Screen* screen, std::string *current_window, std::string *action);
        void draw(Screen*);
        int createfrom(Screen* screen, std::string JSONsource);

    private:
        bool m_window_running; // Should be shown and updated ?
        std::string m_window_name; // Name to identify the window
        
        std::vector<Button*> m_buttons; // Buttons on the window
        Button* m_title; // Title of the window
};

#endif
