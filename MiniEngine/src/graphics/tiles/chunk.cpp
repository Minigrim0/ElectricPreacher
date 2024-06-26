
#include "graphics/tiles/chunk.hpp"
#include "utils/utils.hpp"

namespace MiniEngine::Graphics::Tiling {
// Constructors
Chunk::Chunk()
    : m_absolute_coordinates({0, 0}), m_chunk_size({0, 0}), m_position({0, 0}), m_texture(nullptr),
      m_elements(nullptr) {}

Chunk::Chunk(int chunk_size, SDL_Point position)
    : m_absolute_coordinates({0, 0}), m_chunk_size({chunk_size, chunk_size}),
      m_position({position.x, position.y, 0, 0}), m_texture(nullptr), m_elements(nullptr) {}

Chunk::~Chunk() {}

// Getters
SDL_Point Chunk::get_position() const { return m_absolute_coordinates; }

// Setters
void Chunk::set_position(int x, int y) {
    m_absolute_coordinates = {x, y};
    m_position.x = x;
    m_position.y = y;
}

void Chunk::set_position(SDL_Point position) {
    m_absolute_coordinates = position;
    m_position = {position.x, position.y, 0, 0};
}

/**
 * @brief Loads the chunk from the json file
 *
 * @param chunk The json description of the chunk in tiled format
 * @param tilesets The available tilesets
 * @param screen The screen to render the chunk on
 */
void Chunk::load(nlohmann::json chunk, std::map<std::string, TileSet *> *tilesets,
                 MiniEngine::Screen *screen) {
    // TODO: Change this hardcoded tileset name
    TileSet *tileset = (*tilesets)["Outside"];

    m_chunk_size = {chunk["width"], chunk["height"]};
    m_position = {chunk["x"].get<int>() * tileset->get_tile_width(),
                  chunk["y"].get<int>() * tileset->get_tile_height(),
                  m_chunk_size.x * tileset->get_tile_width(),
                  m_chunk_size.y * tileset->get_tile_height()};

    m_elements = static_cast<Tile **>(malloc(m_chunk_size.x * m_chunk_size.y * sizeof(Tile)));

    // Create an empty transparent surface for chunk pre-rendering
    SDL_Surface *surface = SDL_CreateRGBSurface(0, m_chunk_size.x * tileset->get_tile_width(),
                                                m_chunk_size.y * tileset->get_tile_height(), 32,
                                                0xff, 0xff00, 0xff0000, 0xff000000);

    for (int y = 0; y < m_chunk_size.y; y++) {
        for (int x = 0; x < m_chunk_size.x; x++) {
            Tile *newElem =
                new Tile({x * tileset->get_tile_width(), y * tileset->get_tile_height()});
            newElem->set_texture(
                tileset, chunk["data"][coord_to_index(x, y, m_chunk_size.x)].get<int>() - 1);
            // Draw the element on the surface
            newElem->draw(surface);
            m_elements[coord_to_index(x, y, m_chunk_size.x)] = newElem;
        }
    }

    // Convert the surface to a texture
    m_texture = SDL_CreateTextureFromSurface(screen->get_renderer(), surface);
}

/**
 * @brief Renders the chunk on the screen
 *
 * @param screen The screen object to render the chunk to
 * @param position The position on the screen
 */
void Chunk::OnRender(MiniEngine::Screen *screen) {
    SDL_RenderCopy(screen->get_renderer(), m_texture, NULL, &m_position);
}

bool Chunk::OnEvent(SDL_Event *event) { return false; }

void Chunk::OnUpdate(int time_elapsed) {}
} // namespace MiniEngine::Graphics::Tiling