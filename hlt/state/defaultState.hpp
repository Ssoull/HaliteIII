#ifndef DEFAULTSTATE_H
#define DEFAULTSTATE_H

#include "state.hpp"
//Default state the ships are created with, it's only used as a hacky solution to use the onStateEnter() of the harvesting state.
class DefaultState : public State
{
private:
  /* data */
  Position m_bestPosition;

public:
  virtual void update(Ship *ship_to_update, std::shared_ptr<GameMap> &game_map) override;
  virtual void onStateExit() override;
  virtual void onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity) override;
  virtual Position computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map) override;

  // Getter
  virtual Position getDestination() override;
};

#endif