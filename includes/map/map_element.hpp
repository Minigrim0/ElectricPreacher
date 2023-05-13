#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_render.h>

#include "screen/screen.hpp"
#include "screen/tileset.hpp"
#include "player/player.hpp"

class MapElement
{
public:
    // Constructors
    MapElement(bool Solid, std::string type);
    MapElement(bool Solid, std::string type, SDL_Point position);
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

class GroundElement : public MapElement
{
public:
    explicit GroundElement(SDL_Point position);
    ~GroundElement() = default;

    void interact(Player *player) override;

private:
};
