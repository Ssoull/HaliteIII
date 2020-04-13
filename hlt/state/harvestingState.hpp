#ifndef HARVESTINGSTATE_H
#define HARVESTINGSTATE_H

#include "state.hpp"

const int DISTANCE_WEIGHT = 2;
const int CHECK_DISTANCE = 10;

class HarvestingState : public State
{
private:
  /* data */
  Position m_bestPosition;

public:
  virtual void update(Ship *ship_to_update, std::shared_ptr<GameMap> &game_map) override;
  virtual void onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity) override;
  virtual void onStateExit() override;
  virtual Position computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map) override;

  // Getter
  virtual Position getDestination() override;
};

#endif