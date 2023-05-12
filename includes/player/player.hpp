#pragma once

#include "SDL.h"

#include "screen/screen.hpp"

enum class STATUS
{
    IDLE,
    WALKING,
    ATTACKING,
    DEAD
};

enum class DIR
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player
{
public:
    Player();
    ~Player();

    // Getters
    inline SDL_Rect get_position() const { return m_position; }

    // Setters
    void set_position(SDL_Rect position);
    void set_position(int x, int y);

    // Others
    void init(Screen *sc);

    void handle_event(SDL_Event *event);
    void update(Screen *sc);
    int draw(Screen *sc) const;

    void move(SDL_Event *event);

private:
    void walk(Screen *sc);

    SDL_Rect m_position;  // The position on the map (in tiles)
    float m_walking_offset;  // The offset of the player when walking
    SDL_Texture *m_texture;

    int m_speed;  // Pixels per second

    STATUS m_status;
    DIR m_dir;
};
