#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_render.h>

#include "screen/screen.hpp"
#include "screen/tileset.hpp"
#include "player/player.hpp"

namespace MAP_ELEMENT
{
    const std::string GROUND = "ground";
    const std::string WALL = "wall";
    const std::string DOOR = "door";
    const std::string INTERACTIBLE = "interactible";
    const std::string NPC = "npc";
    const std::string ENEMY = "enemy";
} // namespace MAP_ELEMENT

/**
 * @author Minigrim0
 * @brief A map element is an element of the map, which can be interacted with
 * This class is abstract, and should be inherited by other classes
 */
class MapElement
{
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
    void set_texture(TileSet *tileset, int id);

    // Others
    int draw(SDL_Surface *dest);

    virtual void interact(Player *player) = 0;

private:
    bool m_is_solid;
    TileSet *m_tileset;
    int m_texture_id;

    SDL_Point m_texture_size;
    SDL_Rect m_position;
    std::string m_type;
};

/**
 * @author Minigrim0
 * @brief A ground element is a map element that can be walked on
 * It is not solid, and cannot be interacted with
 * It may contain a hitbox, but it is not required (For a cliff for example)
 */
class GroundElement : public MapElement
{
public:
    explicit GroundElement(SDL_Point position);
    ~GroundElement() = default;

    void interact(Player *player) override;

private:
};
