#pragma once

#include <SDL.h>

#include <core/screen.hpp>
#include <event/interactible.hpp>

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
class Player : public MiniEngine::Event::Interactible
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
    void init(MiniEngine::Screen *sc);

    bool OnEvent(SDL_Event *event) override;
    void OnUpdate(int time_elapsed) override;
    void OnRender(MiniEngine::Screen *sc) override;

private:
    bool move(SDL_Keycode sym);
    void walk(MiniEngine::Screen *sc);
    void update_position();

    SDL_Rect m_position;  //! The position on the map (in tiles)
    SDL_Rect m_draw_position;  //! The position on the screen (in pixels)
    float m_walking_offset;  //! The offset of the player when walking
    SDL_Texture *m_texture;  //! Temporary texture, will be replaced by an animation

    int m_speed;  //! Pixels per second

    STATUS m_status;
    DIR m_dir;
};
