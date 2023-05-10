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
    virtual ~MapElement() = default;

    // Getters
    std::string get_type() const;
    bool is_solid() const;

    // Setters
    void set_solidity(bool);
    void set_texture(TileSet *tileset, int id, SDL_Point tileset_size, Screen *screen);

    // Others
    int draw(Screen *, int, int);
    int draw(Screen *, SDL_Rect);

    virtual void interact(Player *player) = 0;

private:
    bool m_is_solid;
    TileSet *m_tileset;
    int m_texture_id;

    SDL_Point m_texture_size;
    std::string m_type;
};

class GroundElement : public MapElement
{
public:
    GroundElement();
    ~GroundElement() = default;

    void interact(Player *player) override;

private:
};
