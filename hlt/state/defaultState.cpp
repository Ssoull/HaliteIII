#include "defaultState.hpp"

#include "harvestingState.hpp"

void DefaultState::update(Ship *entity_to_update, std::shared_ptr<GameMap> &game_map)
{
  //On the first update the default state will change the ship state to harvesting state
  entity_to_update->setState(std::make_shared<HarvestingState>(), game_map);
}

void DefaultState::onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity) {}

void DefaultState::onStateExit() {}

Position DefaultState::computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map)
{
  return Position(0, 0);
}

Position DefaultState::getDestination()
{
  return Position(0, 0);
}
