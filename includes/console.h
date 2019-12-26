#ifndef console_h
    #define console_h

#include <vector>

#include "screen.h"
#include "button.h"
#include "text_input.h"
#include "widgets.h"

class Console: public Widget{
    public:
        // Constructors
        Console();
        Console(TTF_Font*);
        Console(const Console&);
        ~Console();

        Console& operator=(const Console&);

        // Getters


        // Setters
        int set_font(TTF_Font*);
        int set_font(std::string, int);

        // Others
        int draw(Screen*) override;
        int update(SDL_Event) override;
        int update_layout(Screen*);

    private:
        std::vector<Button> m_history;
        TextInput* m_input;
        Button* m_send_button;
        TTF_Font* m_font;
};

#endif
