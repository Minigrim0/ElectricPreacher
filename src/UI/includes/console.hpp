#ifndef console_h
    #define console_h

/**
    name : console.h
    purpose : Handles a complete console with text input for the user,
    text output from the rest of the game, the drawing of itself and the updating

    @author : mingirim0
    @version : 1.0
*/

#include <vector>

#include "screen.hpp"
#include "button.hpp"
#include "text_input.hpp"
#include "widgets.hpp"

class Console: public Widget{
    public:
        // Constructors
        Console();
        Console(int, int);
        Console(int, int, int);
        Console(int, int, int, int);
        Console(TTF_Font*);
        ~Console();

        Console& operator=(const Console&);

        // Getters


        // Setters
        void set_position(int, int);
        void set_size(int, int);
        int set_font(TTF_Font*);
        int set_font(std::string, int);

        // Others
        void init(Screen*);
        int draw(Screen*) override;
        int update(SDL_Event*, Screen*) override;
        int update_layout(Screen*);
        void init_send_button();
        void create_entry(Screen*);

    private:
        SDL_Rect m_rect;
        std::vector<Button*> m_history; //The previous inputs and outputs
        TextInput* m_input;
        Button* m_send_button;
        TTF_Font* m_font;
        SDL_Texture* m_background_texture;

        int m_nb_visible_lines;
        int m_line_height;

        Uint8 m_alpha;
};

#endif
