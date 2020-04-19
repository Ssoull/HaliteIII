#ifndef HARVESTINGSTATE_H
#define HARVESTINGSTATE_H

#include "state.hpp"

/* constants */
const int DISTANCE_WEIGHT = 1; //Weight applied to the distance between the ship and the evaluated cell when calculating the best destination
const float DROPOFF_DISTANCE_WEIGHT = 1.f; //Weight applied to the distance between the evaluated cell and the closest dropoff when computing the best destination
const int CHECK_DISTANCE = 10; //Size of the radius where the ship checks for a dropoff or a suitable cell to harvest

//This state is used by the ships when thay harvest halite
//When entering this state a destination will be computed
//The ship will exit this state when it's full
//The ship in this state will change the cell wher it harvests when the cell is empty
class HarvestingState : public State
{
private:
  /* data */
  Position m_bestPosition; //Used to determine the best position to create a dropoff if non is find around the ship
  Position m_closestDropoff; //The position if the clisest dropoff

public:
 //See state.hpp for more informations
  virtual void update(Ship *ship_to_update, std::shared_ptr<GameMap> &game_map) override; 
  virtual void onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity) override;
  virtual void onStateExit() override;
  virtual Position computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map) override;

  int distanceToClosestDropoff(Position &start_pos, std::shared_ptr<GameMap> &game_map); //Check the game map to find the closest dropoff

  // Getter
  virtual Position getDestination() override;
};

#endif