#include "map/map_element.hpp"
#include "player/player.hpp"

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
