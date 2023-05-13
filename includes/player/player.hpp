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

private:
    void move(SDL_Keycode sym);
    void walk(Screen *sc);
    void update_position();

    SDL_Rect m_position;  // The position on the map (in tiles)
    SDL_Rect m_draw_position;  // The position on the screen (in pixels)
    float m_walking_offset;  // The offset of the player when walking
    SDL_Texture *m_texture;

    int m_speed;  // Pixels per second

    STATUS m_status;
    DIR m_dir;
};
