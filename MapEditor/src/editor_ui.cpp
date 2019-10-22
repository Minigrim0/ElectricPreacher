/**
    name : editor_ui.cpp
    purpose : contains the source code for the EditorUI class

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>

#include "../includes/editor_ui.h"
#include "../../includes/json/json.h"
#include "../../includes/screen.h"
#include "../../includes/constants.h"

//Constructors
EditorUI::EditorUI()
:m_current_layer(0),
m_caption_image(nullptr),
m_header_image(nullptr),
m_grid(nullptr),
m_grid_pos({0, 0, 0, 0}),
m_font_color({0, 0, 0, 0}),
m_current_chunk(nullptr)
{
}

EditorUI::EditorUI(EditorUI& ui)
:m_current_layer(ui.get_current_layer()),
m_caption_image(nullptr),
m_header_image(nullptr),
m_grid(nullptr),
m_grid_pos({0, 0, 0, 0}),
m_font_color({0, 0, 0, 0}),
m_current_chunk(nullptr)
{
}

EditorUI::~EditorUI(){
    SDL_FreeSurface(m_grid);
}

//Overrides
EditorUI& EditorUI::operator=(const EditorUI& ui){
    m_current_layer = ui.get_current_layer();

    return *this;
}

//Getters
int EditorUI::get_current_layer() const{return m_current_layer;}

SDL_Rect EditorUI::get_grid_pos() const{return m_grid_pos;}

//Setters
void EditorUI::set_grid_pos(SDL_Rect pos){
    m_grid_pos = pos;
}

void EditorUI::set_grid_pos(int x, int y){
    m_grid_pos.x = x;
    m_grid_pos.y = y;
}

int EditorUI::set_font(std::string path){
    int sizes[] = {12, 15, 20, 25, 30};
    int result = 0;
    for(int x=0;x<5;x++){
        m_fonts[x] = TTF_OpenFont(path.c_str(), sizes[x]);
        if(m_fonts[x] == NULL){
            result = 1;
            std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
        }
    }
    return result;
}

short EditorUI::set_element(std::string path){
    std::ifstream json_in(path.c_str());
    Json::Value root;
    json_in >> root;

    const Json::Value buttons = root["Buttons"];
    for (unsigned int index=0;index<buttons.size();++index)
        std::cout << buttons[index].asString() << std::endl;

    json_in.close();
    return 0;
}

//Others
void EditorUI::draw(Screen* screen){
    screen->blit_surface(m_grid, NULL, m_grid_pos);
    screen->blit_surface(m_header_image, NULL, 0, 0);
    screen->blit_surface(m_caption_image, NULL, 5, 5);
}

void EditorUI::init_ui_elements(Screen* screen){
    set_element("lul");
    create_grid();
    create_header(screen);
    m_caption_image = TTF_RenderText_Blended(m_fonts[2], screen->get_caption().c_str(), m_font_color);

}

void EditorUI::create_grid(){
    m_grid = SDL_CreateRGBSurface(0, 32*CHUNK_SIZE, 32*CHUNK_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(m_grid, NULL, SDL_MapRGB(m_grid->format, 200, 200, 200));

    SDL_Surface* horizontal_line = SDL_CreateRGBSurface(0, 32*CHUNK_SIZE, 1, 32, 0, 0, 0, 0);
    SDL_Surface* vertical_line = SDL_CreateRGBSurface(0, 1, 32*CHUNK_SIZE, 32, 0, 0, 0, 0);

    SDL_Rect rect;
    for(int x=1;x<CHUNK_SIZE;x++){
        rect.x = x*32;
        rect.y = 0;
        SDL_BlitSurface(vertical_line, NULL, m_grid, &rect);
        rect.x = 0;
        rect.y = x*32;
        SDL_BlitSurface(horizontal_line, NULL, m_grid, &rect);
    }
}

void EditorUI::create_header(Screen* screen){
    m_header_image = SDL_CreateRGBSurface(0, EDITOR_SCREEN_X, 50, 32, 0, 0, 0, 0);
    SDL_Surface* line = SDL_CreateRGBSurface(0, EDITOR_SCREEN_Y, 1, 32, 0, 0, 0, 0);
    SDL_Color curr_color;
    curr_color.r = 100;
    curr_color.g = 120;
    curr_color.b = 200;
    curr_color.a = 255;
    SDL_Rect pos;pos.y = 0;pos.x = 0;
    for(int x=0;x<50;x++){
        pos.y = x;
        SDL_FillRect(line, NULL, SDL_MapRGB(screen->get_format(), curr_color.r, curr_color.g, curr_color.b));
        SDL_BlitSurface(line, NULL, m_header_image, &pos);
        curr_color.r = static_cast<Uint8>(static_cast<int>(curr_color.r) - 1);
        curr_color.g = static_cast<Uint8>(static_cast<int>(curr_color.g) - 2);
        curr_color.b = static_cast<Uint8>(static_cast<int>(curr_color.b) - 3);
    }
}
