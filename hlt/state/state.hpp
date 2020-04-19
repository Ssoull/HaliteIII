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
	bool shouldCreateDropoff; //Used to determine if the ship will create a dropoff or not
	virtual void update(Ship *ship_to_update, std::shared_ptr<GameMap> &game_map) = 0; //Called when the ship is updated, allow to recompute a better destination or change state
	virtual void onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity) = 0; //Called by the ship when changing state, used to initialize destination or check surroundings
	virtual void onStateExit() = 0; //Called when the ship changes its state

	//Should return the best position according to the current state
	virtual Position computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map) = 0;

	// Getter
	virtual Position getDestination() = 0; //Return a Position that is the destination of the ship either a cell when harvesting or a dropoff/shipyard when dropping halite
};
#endif