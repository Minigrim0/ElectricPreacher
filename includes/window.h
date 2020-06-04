#ifndef window_h
    #define window_h

#include <iostream>
#include <SDL2/SDL.h>

#include "button.h"

class Window{
    public:
        Window() = default;
        virtual ~Window() = default;

        //Getter
        bool is_running() const;
        std::string get_title() const;

        //Setter
        bool set_running(bool);
        bool set_title(bool);

        //Others
        int add_button(Button*);
        void update();
        void draw();

    private:
        bool m_window_running;
        Button* m_buttons;
        std::string m_window_title;
};

#endif
