#ifndef STATE_H
#define STATE_H

#include "../src/position.hpp"
#include "../src/game_map.hpp"
#include "../src/ship.hpp"

// Error of cyclic dependency between state and ship
class Ship;

// Interface
class State
{
private:
public:
	bool shouldCreateDropoff;
	virtual void update(Ship *ship_to_update, std::shared_ptr<GameMap> &game_map) = 0;
	virtual void onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity) = 0;
	virtual void onStateExit() = 0;
	//Should return the best position according to the current state
	virtual Position computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map) = 0;

	// Getter
	virtual Position getDestination() = 0;
};
#endif