#ifndef STATE_H
#define STATE_H

#include "../src/position.hpp"
#include "../src/game_map.hpp"

// Error of cyclic dependency between state and ship
class Ship;

class State
{
private:
public:
    State();
    virtual void update();
    virtual void update(Ship *shipToUpdate);
    virtual void update(Ship *shipToUpdate, std::shared_ptr<GameMap> &game_map);
    virtual void onStateEnter();
    virtual void onStateExit();
    //Return the direction the shilp should use
    virtual Direction computeNextDirection(const Position &dest, std::shared_ptr<GameMap> &game_map);
    //Should return the best position according to the current state
    virtual Position computeBestDestination(const Position &startPos, std::shared_ptr<GameMap> &game_map);
    virtual Position getDestination();
};
#endif