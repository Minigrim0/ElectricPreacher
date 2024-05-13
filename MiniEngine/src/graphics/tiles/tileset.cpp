#include "graphics/tiles/tileset.hpp"

#include <tinyxml2.h>

#include "core/log.hpp"

namespace MiniEngine::Graphics::Tiling {
// Constructors
TileSet::TileSet()
    : _texture(nullptr), _width(0), _height(0), _name("null"), _rects(), _tile_width(32),
      _tile_height(32) {}

TileSet::TileSet(SDL_Surface *img)
    : _texture(img), _width(img->w), _height(img->h), _name("null"), _rects(), _tile_width(32),
      _tile_height(32) {}

TileSet::~TileSet() { SDL_FreeSurface(_texture); }

// Getters
const SDL_Rect *TileSet::get_sub(int x, int y) const {
    long unsigned int pos = static_cast<long unsigned int>(y * _width / 32 + x);
    if (pos > _rects.size())
        return NULL;
    return &_rects.at(pos);
}

// Setters
void TileSet::load(Screen *screen, fs::path filePath) {
    tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument();
    doc->LoadFile(filePath.string().c_str());

    tinyxml2::XMLElement *tileset_element = doc->FirstChildElement("tileset");
    if (tileset_element == nullptr) {
        ME_CORE_WARN("tileset_element is null");
        return;
    }

    _tile_width = std::atoi(tileset_element->Attribute("tilewidth"));
    _tile_height = std::atoi(tileset_element->Attribute("tileheight"));

    tinyxml2::XMLElement *tileset_image = tileset_element->FirstChildElement("image");

    _width = std::atoi(tileset_image->Attribute("width"));
    _height = std::atoi(tileset_image->Attribute("height"));
    _name = tileset_element->Attribute("name");

    _texture = screen->loadSurface(
        (filePath.remove_filename() / tileset_image->Attribute("source")).string());

    if (set_array() != 0)
        ME_CORE_ERROR("Error while setting array");
}

// Others
int TileSet::set_array() {
    if (_texture == NULL)
        return 1;
    for (int y = 0; y < _height; y += 32) {
        for (int x = 0; x < _width; x += 32) {
            SDL_Rect tmp_rect = {x, y, 32, 32};
            _rects.push_back(tmp_rect);
        }
    }
    return 0;
}
} // namespace MiniEngine::Graphics::Tiling
