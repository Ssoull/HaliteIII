#ifndef DROPSTATE_H
#define DROPSTATE_H

#include "state.hpp"

const int DROPOFF_CHECK_RADIUS = 8;

class DropState : public State
{
private:
  Position m_bestDropLocation;
  bool willBeDropoff = false;
  Position m_dropoffLocation;
  int m_nbOfTurnsStuck = 0;

public:
  virtual void update(Ship *entity_to_update, std::shared_ptr<GameMap> &game_map) override;
  virtual void onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity) override;
  virtual void onStateExit() override;
  virtual Position getDestination() override;
  virtual Position computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map) override;
  //On state enter check if there is a dropoff nearby
  bool checkForDropoff(std::shared_ptr<GameMap> &game_map, int radius, Position center);

  //TODO : implement statics methods in game map for distance and compute radius in toroidal space
};

#endif