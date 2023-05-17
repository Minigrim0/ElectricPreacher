#pragma once

#include "SDL.h"

#include <core/screen.hpp>

#include "constants.hpp"

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

/**
 * @author Minigrim0
 * @brief The player class
 * The player is the character controlled by the player
 * The player can walk, attack, interact with objects and NPCs
 * 
 * The player is represented by a rectangle, which position is in tiles
 * The player is drawn on screen, and can be animated
 */
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
    void init(CORE::Screen *sc);

    void handle_event(SDL_Event *event);
    void update(CORE::Screen *sc);
    int draw(CORE::Screen *sc) const;

private:
    void move(SDL_Keycode sym);
    void walk(CORE::Screen *sc);
    void update_position();

    SDL_Rect m_position;  //! The position on the map (in tiles)
    SDL_Rect m_draw_position;  //! The position on the screen (in pixels)
    float m_walking_offset;  //! The offset of the player when walking
    SDL_Texture *m_texture;  //! Temporary texture, will be replaced by an animation

    int m_speed;  //! Pixels per second

    STATUS m_status;
    DIR m_dir;
};
