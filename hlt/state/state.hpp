#ifndef STATE_H
#define STATE_H

#include "../src/position.hpp"
#include "../src/game_map.hpp"

// Error of cyclic dependency between state and ship
class Ship;

class State
{
public:
    virtual void update() = 0;
    virtual void update(Ship *ship_to_update) = 0;
    virtual void update(Ship *ship_to_update, std::shared_ptr<GameMap> &game_map) = 0;
    virtual void onStateEnter() = 0;
    virtual void onStateExit() = 0;
    //Return the direction the shilp should use
    virtual Direction computeNextDirection(const Position &dest, std::shared_ptr<GameMap> &game_map);
    //Should return the best position according to the current state
    virtual Position computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map) = 0;

    // Getter
    virtual Position getDestination() = 0;
};
#endif