#ifndef editor_ui_h
    #define editor_ui_h

/**
    name : editor_ui.cpp
    purpose : Contains the prototypes of the EditorUI class

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>

#include "constants.h"
#include "../../includes/ground_element.h"
#include "../../includes/screen.h"

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

        //Others
        void draw(Screen*);
        void create_grid();
    private:
        int m_current_layer;

        SDL_Surface* m_grid;

        GroundElement m_level_1[CHUNK_SIZE][CHUNK_SIZE];
};

#endif
