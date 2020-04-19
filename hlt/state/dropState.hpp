#ifndef DROPSTATE_H
#define DROPSTATE_H

#include "state.hpp"

const int DROPOFF_CHECK_RADIUS = 8; //Size of the radisu where the ship look for a dropoff

//State used by the ship when it's full of halite and needs a place to drop it
//When entering this state checks for a dropoff, if no dropoff is found the ship will become one
class DropState : public State
{
private:
  Position m_bestDropLocation;
  bool willBeDropoff = false; //By defayult the ships are not meant to become dropoff
  Position m_dropoffLocation;
  int m_nbOfTurnsStuck = 0; //Used to increase the radius size when looking for a dropoff

public:
//See state.hpp
  virtual void update(Ship *entity_to_update, std::shared_ptr<GameMap> &game_map) override;
  virtual void onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity) override;
  virtual void onStateExit() override;
  virtual Position getDestination() override;
  virtual Position computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map) override;
  //On state enter check if there is a dropoff nearby
  bool checkForDropoff(std::shared_ptr<GameMap> &game_map, int radius, Position center); //Check for a dropoff with the game map as parameter, the radius used is by default the constant DROPOFF_CHECK_RADIUS
};

#endif