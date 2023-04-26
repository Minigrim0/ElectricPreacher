#include "screen/tileset.hpp"

#include <iostream>
#include <SDL.h>
#include <tinyxml2.h>

#include "screen/screen.hpp"

//Constructors
TileSet::TileSet()
:m_tex(nullptr),
m_width(0),
m_height(0),
m_name("null"),
m_rects()
{}

TileSet::TileSet(SDL_Texture* img)
:m_tex(img),
m_width(0),
m_height(0),
m_name("null"),
m_rects()
{
    SDL_QueryTexture(m_tex, NULL, NULL, &m_width, &m_height);
}

TileSet::~TileSet(){
    SDL_DestroyTexture(m_tex);
}

//Override
TileSet& TileSet::operator=(const TileSet& set){
    m_tex = set.get_texture();

    return *this;
}

SDL_Rect* TileSet::operator[](std::size_t idx){
    return &(m_rects[idx]);
}

//Getters
SDL_Texture* TileSet::get_texture() const{return m_tex;}

const SDL_Rect* TileSet::get_sub(int x, int y) const{
    long unsigned int pos = static_cast<long unsigned int>(y*m_width/32 + x);
    if(pos > m_rects.size()) return NULL;
    return &m_rects.at(pos);
}

int TileSet::blit_sub(Screen* sc, int img_x, int img_y, int pos_x, int pos_y) const{
    SDL_Rect pos = {pos_x, pos_y, 0, 0};
    SDL_RenderCopy(sc->get_renderer(), m_tex, get_sub(img_x, img_y), &pos);

    return 0;
}

int TileSet::get_width() const{
    return m_width;
}

int TileSet::get_height() const{
    return m_height;
}

std::string TileSet::get_name() const{
    return m_name;
}

//Setters
void TileSet::set_image(Screen* screen, std::string image){
    m_tex = screen->load_texture(image.c_str());
    SDL_QueryTexture(m_tex, NULL, NULL, &m_width, &m_height);

    if(m_tex == NULL || m_width%32 != 0 || m_height%32 != 0)
        exit(EXIT_FAILURE);
}

void TileSet::load(Screen* screen, fs::path filePath){
    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
    doc->LoadFile(filePath.c_str());

    tinyxml2::XMLElement* tileset_element = doc->FirstChildElement("tileset");
    if(tileset_element == nullptr) std::cout << "tileset_element is null" << std::endl;
    tinyxml2::XMLElement* tileset_image = tileset_element->FirstChildElement("image");

    m_width = std::stoi(tileset_element->Attribute("tilewidth"));
    m_height = std::stoi(tileset_element->Attribute("tileheight"));
    m_name = tileset_element->Attribute("name");

    m_tex = screen->load_texture(filePath.remove_filename() / tileset_image->Attribute("source"));

    set_array();
}

//Others
int TileSet::set_array(){
    if(m_tex == NULL) return 1;
    for(int y=0;y<m_height;y+=32){
        for(int x=0;x<m_width;x+=32){
            SDL_Rect tmp_rect = {x, y, 32, 32};
            m_rects.push_back(tmp_rect);
        }
    }
    return 0;
}
