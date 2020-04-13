#include "harvestingState.hpp"
#include "dropState.hpp"

#include "../utils/log.hpp"

void HarvestingState::update(Ship *entity_to_update, std::shared_ptr<GameMap> &game_map)
{
  if (game_map->at(m_bestPosition)->isOccupied() == true && entity_to_update->getPosition() != m_bestPosition)
  {
    custom_logger::log("Cell occupied, replaning");
    m_bestPosition = computeBestDestination(Position(0, 0), game_map);
  }

  if (entity_to_update->isFull() || entity_to_update->getHalite() > 900)
  {
    entity_to_update->setState(std::make_shared<DropState>(), game_map);
  }

  if (game_map->at(entity_to_update->getPosition())->getHalite() == 0)
  {
    m_bestPosition = computeBestDestination(entity_to_update->getPosition(), game_map);
  }
  //TODO add looking for neighbors for halite when cell halite is low
}

void HarvestingState::onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity)
{
  //Actions to perform on state enter (e g : set target...)
  m_bestPosition = computeBestDestination(Position(0, 0), game_map);
}

void HarvestingState::onStateExit()
{
  //Actions to perform on state exit
}

Position HarvestingState::computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map)
{
  Position bestPositionTemp = Position(0, 0);
  int maxHalite = 0;
  for (int x = 0; x < game_map->getWidth(); ++x)
  {
    for (int y = 0; y < game_map->getHeight(); ++y)
    {
      if (game_map->at(Position(x, y))->getHalite() > maxHalite && game_map->at(Position(x, y))->isOccupied() == false)
      {
        bestPositionTemp = Position(x, y);
        maxHalite = game_map->at(Position(x, y))->getHalite();
      }
    }
  }
  custom_logger::log("[HarvestingState::computeBestDestination] Best Pos : " + bestPositionTemp.to_string());
  return bestPositionTemp;
}

// Getter
Position HarvestingState::getDestination()
{
  return m_bestPosition;
}