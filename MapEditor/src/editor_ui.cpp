/**
    name : editor_ui.cpp
    purpose : contains the source code for the EditorUI class

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>
#include <SDL2/SDL.h>

#include "../includes/editor_ui.h"
#include "../../includes/screen.h"

//Constructors
EditorUI::EditorUI(): m_grid(NULL){
    m_current_layer = 0;

    create_grid();
}

EditorUI::EditorUI(EditorUI& ui){
    m_current_layer = ui.get_current_layer();
}

EditorUI::~EditorUI(){
    SDL_FreeSurface(m_grid);
}

//Overrides
EditorUI& EditorUI::operator=(const EditorUI& ui){
    m_current_layer = ui.get_current_layer();

    return *this;
}

//Others
int EditorUI::get_current_layer() const{return m_current_layer;}

//Others
void EditorUI::draw(Screen* screen){
    screen->blit_surface(m_grid, NULL, 0, 0);
}

void EditorUI::create_grid(){
    m_grid = SDL_CreateRGBSurface(0, 32*CHUNK_SIZE, 32*CHUNK_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(m_grid, NULL, SDL_MapRGB(m_grid->format, 200, 200, 200));

    SDL_Surface* horizontal_line = SDL_CreateRGBSurface(0, 32*CHUNK_SIZE, 1, 32, 0, 0, 0, 0);
    SDL_Surface* vertical_line = SDL_CreateRGBSurface(0, 1, 32*CHUNK_SIZE, 32, 0, 0, 0, 0);

    SDL_Rect rect;
    for(int x=0;x<CHUNK_SIZE;x++){
        rect.x = x*32;
        rect.y = 0;
        SDL_BlitSurface(vertical_line, NULL, m_grid, &rect);
        rect.x = 0;
        rect.y = x*32;
        SDL_BlitSurface(horizontal_line, NULL, m_grid, &rect);
    }
}
