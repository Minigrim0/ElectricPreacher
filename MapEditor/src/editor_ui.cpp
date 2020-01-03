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

#include "../../includes/widgets.h"

//Constructors
EditorUI::EditorUI()
:m_current_layer(0),
m_caption_image(nullptr),
m_header_image(nullptr),
m_grid(nullptr),
m_grid_pos({0, 0, 0, 0}),
m_font_color(new SDL_Color),
m_current_chunk(nullptr),
m_buttons(std::vector<Button*>())
{
    m_font_color->r = 0;
    m_font_color->g = 0;
    m_font_color->b = 0;
    m_font_color->a = 255;

    m_grid_pos.x = 0;
    m_grid_pos.y = 0;
    m_grid_pos.w = 0;
    m_grid_pos.h = 0;
}

EditorUI::EditorUI(EditorUI& ui)
:m_current_layer(ui.get_current_layer()),
m_caption_image(nullptr),
m_header_image(nullptr),
m_grid(nullptr),
m_grid_pos({0, 0, 0, 0}),
m_font_color(new SDL_Color),
m_current_chunk(nullptr),
m_buttons(std::vector<Button*>())
{
    m_font_color->r = 0;
    m_font_color->g = 0;
    m_font_color->b = 0;
    m_font_color->a = 255;

    m_grid_pos.x = 0;
    m_grid_pos.y = 0;
    m_grid_pos.w = 0;
    m_grid_pos.h = 0;
}

EditorUI::~EditorUI(){
    for(int x=0;x<5;x++)
        TTF_CloseFont(m_fonts[x]);
    SDL_FreeSurface(m_header_image);
    SDL_FreeSurface(m_caption_image);
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

short EditorUI::set_element(Screen* screen, std::string path){
    std::ifstream json_in(path.c_str());
    Json::Value root;
    json_in >> root;

    //Setup Buttons
    const Json::Value buttons = root["Buttons"];
    for (unsigned int index=0;index<buttons.size();++index){
        m_buttons.push_back(new Button);
        m_buttons.back()->set_text(buttons[index]["name"].asString());

        m_buttons.back()->set_position(
            buttons[index]["position_x"].asInt(),
            buttons[index]["position_y"].asInt()
        );

        m_buttons.back()->set_size(
            buttons[index]["size_x"].asInt(),
            buttons[index]["size_y"].asInt()
        );

        m_buttons.back()->set_text_color(
            buttons[index]["text-color"]["r"].asInt(),
            buttons[index]["text-color"]["g"].asInt(),
            buttons[index]["text-color"]["b"].asInt()
        );

        m_buttons.back()->set_background_color(
            buttons[index]["background-color"]["r"].asInt(),
            buttons[index]["background-color"]["g"].asInt(),
            buttons[index]["background-color"]["b"].asInt()
        );

        m_buttons.back()->set_contour_color(
            buttons[index]["contour-color"]["r"].asInt(),
            buttons[index]["contour-color"]["g"].asInt(),
            buttons[index]["contour-color"]["b"].asInt()
        );

        //Set text-position, via text or absolute coordinates
        if(buttons[index]["text_position_type"].asString() == "txt")
            m_buttons.back()->set_text_pos(
                buttons[index]["text-position"].asString()
            );
        else
            m_buttons.back()->set_text_pos(
                buttons[index]["text-position_x"].asInt(),
                buttons[index]["text-position_y"].asInt()
            );

        //Finally update the button image
        m_buttons.back()->update_layout(
            screen,
            m_fonts[buttons[index]["font_size"].asInt()]
        );
    }

    //Setup grid
    const Json::Value grid = root["Grid"];
    m_grid_pos.x = grid["position_x"].asInt();
    m_grid_pos.y = grid["position_y"].asInt();

    json_in.close();
    return 0;
}

//Others
void EditorUI::draw(Screen* screen){
    screen->blit_surface(m_grid, NULL, m_grid_pos);
    screen->blit_surface(m_header_image, NULL, 0, 0);
    screen->blit_surface(m_caption_image, NULL, 5, 5);
    for(long unsigned int x=0;x<m_buttons.size();++x){
        m_buttons[x]->draw(screen);
        m_buttons[x]->update(screen);
    }
}

void EditorUI::init_ui_elements(Screen* screen){
    set_element(screen, "../assets/UI/setup.json");
    create_grid();
    create_header(screen);
    m_caption_image = TTF_RenderText_Blended(
        m_fonts[2], screen->get_caption().c_str(),
        *m_font_color);
}

void EditorUI::create_grid(){
    m_grid = SDL_CreateRGBSurface(0, 32*CHUNK_SIZE, 32*CHUNK_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(m_grid, NULL, SDL_MapRGB(m_grid->format, 150, 150, 150));

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

    SDL_FreeSurface(vertical_line);
    SDL_FreeSurface(horizontal_line);
}

void EditorUI::create_header(Screen* screen){
    m_header_image = SDL_CreateRGBSurface(0, EDITOR_SCREEN_X, 50, 32, 0, 0, 0, 0);
    SDL_Surface* line = SDL_CreateRGBSurface(0, EDITOR_SCREEN_X, 1, 32, 0, 0, 0, 0);
    SDL_Color curr_color;
    curr_color.r = 100;
    curr_color.g = 100;
    curr_color.b = 100;
    curr_color.a = 255;
    SDL_Rect pos;pos.y = 0;pos.x = 0;
    for(int x=0;x<50;x++){
        pos.y = x;
        SDL_FillRect(line, NULL, SDL_MapRGB(screen->get_format(), curr_color.r, curr_color.g, curr_color.b));
        SDL_BlitSurface(line, NULL, m_header_image, &pos);
        curr_color.r = static_cast<Uint8>(static_cast<int>(curr_color.r) - 2);
        curr_color.g = static_cast<Uint8>(static_cast<int>(curr_color.g) - 2);
        curr_color.b = static_cast<Uint8>(static_cast<int>(curr_color.b) - 2);
    }

    SDL_FreeSurface(line);
}
