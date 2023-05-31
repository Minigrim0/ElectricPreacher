#pragma once

#include <SDL.h>

#include <core/screen.hpp>
#include <graphics/tileset.hpp>
#include <event/interactible.hpp>

#include "constants.hpp"
#include "player/player.hpp"

/**
 * @author Minigrim0
 * @brief A map element is an element of the map, which can be interacted with
 * This class is abstract, and should be inherited by other classes
 */
class MapElement {
public:
    // Constructors
    MapElement(bool solid, const std::string *type);
    MapElement(bool solid, const std::string *type, SDL_Point position);
    virtual ~MapElement() = default;

    // Getters
    std::string get_type() const;
    bool is_solid() const;

    // Setters
    void set_solidity(bool solid);
    void set_position(SDL_Point position);
    void set_texture(MiniEngine::Graphics::TileSet *tileset, int id);

    // Others
    virtual void interact(Player *player) = 0;

    int draw(SDL_Surface *dest);

protected:
    bool m_is_solid;
    MiniEngine::Graphics::TileSet *m_tileset;
    int m_texture_id;

    SDL_Point m_texture_size;
    SDL_Rect m_position;
    std::string m_type;
};
