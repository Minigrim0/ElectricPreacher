#include "graphics/tileset.hpp"

#include <iostream>
#include <SDL.h>
#include <tinyxml2.h>

#include "core/screen.hpp"

namespace MiniEngine {
namespace Graphics {
// Constructors
TileSet::TileSet()
    : m_tex(nullptr),
      m_width(0),
      m_height(0),
      m_name("null"),
      m_rects()
{
}

TileSet::TileSet(SDL_Surface *img)
    : m_tex(img),
      m_width(0),
      m_height(0),
      m_name("null"),
      m_rects()
{
    m_width = img->w;
    m_height = img->h;
}

TileSet::~TileSet()
{
    SDL_FreeSurface(m_tex);
}

// Override
SDL_Rect *TileSet::operator[](std::size_t idx)
{
    return &(m_rects[idx]);
}

// Getters
const SDL_Rect *TileSet::get_sub(int x, int y) const
{
    long unsigned int pos = static_cast<long unsigned int>(y * m_width / 32 + x);
    if (pos > m_rects.size())
        return NULL;
    return &m_rects.at(pos);
}

// Setters
void TileSet::load(Core::Screen *screen, fs::path filePath)
{
    tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument();
    doc->LoadFile(filePath.string().c_str());

    tinyxml2::XMLElement *tileset_element = doc->FirstChildElement("tileset");
    if (tileset_element == nullptr)
        std::cout << "tileset_element is null" << std::endl;

    m_tile_width = std::atoi(tileset_element->Attribute("tilewidth"));
    m_tile_height = std::atoi(tileset_element->Attribute("tileheight"));

    tinyxml2::XMLElement *tileset_image = tileset_element->FirstChildElement("image");

    m_width = std::atoi(tileset_image->Attribute("width"));
    m_height = std::atoi(tileset_image->Attribute("height"));
    m_name = tileset_element->Attribute("name");

    m_tex = screen->load_image((filePath.remove_filename() / tileset_image->Attribute("source")).string());

    if (set_array() != 0)
        std::cout << "Error while setting array" << std::endl;
}

// Others
int TileSet::set_array()
{
    if (m_tex == NULL)
        return 1;
    for (int y = 0; y < m_height; y += 32)
    {
        for (int x = 0; x < m_width; x += 32)
        {
            SDL_Rect tmp_rect = {x, y, 32, 32};
            m_rects.push_back(tmp_rect);
        }
    }
    return 0;
}

}}