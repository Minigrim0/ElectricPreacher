#ifndef editor_ui_h
    #define editor_ui_h

/**
    name : editor_ui.cpp
    purpose : Contains the prototypes of the EditorUI class

    @author : minigrim0
    @version : 1.0
*/

#include <vector>

#include "../../includes/json/json.h"
#include "../../includes/constants.h"
#include "../../includes/ground_element.h"
#include "../../includes/screen.h"
#include "../../includes/chunk.h"
#include "button.h"

/**
    class : EditorUI
    purpose : Displays a UI for the Map Editor
*/
class EditorUI{
    public:
        //Constructors
        EditorUI();
        EditorUI(EditorUI&);
        ~EditorUI();

        //Overrides
        EditorUI& operator=(const EditorUI&);

        //Getters
        int get_current_layer() const;
        SDL_Rect get_grid_pos() const;

        //Setters
        void set_grid_pos(SDL_Rect);
        void set_grid_pos(int, int);
        int set_font(std::string);
        short set_element(std::string);

        //Others
        void draw(Screen*);
        void init_ui_elements(Screen*);
        void create_grid();
        void create_header(Screen*);

    private:
        int m_current_layer;

        SDL_Surface* m_caption_image;
        SDL_Surface* m_header_image;
        SDL_Surface* m_grid;
        SDL_Rect m_grid_pos;

        TTF_Font* m_fonts[5];
        SDL_Color* m_font_color;

        Chunk* m_current_chunk;
        std::vector<Button*> m_buttons();
};

#endif
