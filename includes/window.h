#ifndef window_h
    #define window_h

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "button.h"
#include "screen.h"

class Window{
    public:
        Window();
        virtual ~Window();

        //Getter
        bool is_running() const;
        std::string get_title() const;

        //Setter
        void set_running(bool);
        void set_title(std::string);

        //Others
        int add_button(Button*);
        void update();
        void draw(Screen*);

    private:
        bool m_window_running;
        std::vector<Button*> m_buttons;
        std::string m_window_title;
};

#endif
