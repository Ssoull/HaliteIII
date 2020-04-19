#include "harvestingState.hpp"
#include "dropState.hpp"

#include "../utils/log.hpp"

void HarvestingState::update(Ship *entity_to_update, std::shared_ptr<GameMap> &game_map)
{
  //Recompute the best destination when the current destination is already occypied by a ship
  if (game_map->at(m_bestPosition)->isOccupied() == true && entity_to_update->getPosition() != m_bestPosition)
  {
    // custom_logger::log("Cell occupied, replaning");
    m_bestPosition = computeBestDestination(entity_to_update->getPosition(), game_map);
  }
  //Change state when the ship is full or with more than 900halite
  if (entity_to_update->isFull() || entity_to_update->getHalite() > 900)
  {
    entity_to_update->setState(std::make_shared<DropState>(), game_map);
  }

  //Recompute destination when the cell is empty
  if (game_map->at(entity_to_update->getPosition())->getHalite() == 0)
  {
    m_bestPosition = computeBestDestination(entity_to_update->getPosition(), game_map);
  }
}

void HarvestingState::onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity)
{
  //Actions to perform on state enter (e g : set target...)
  m_bestPosition = computeBestDestination(entity->getPosition(), game_map);
}

void HarvestingState::onStateExit()
{
  //Actions to perform on state exit
}


//Check for the best destination for the ship
//It uses the halite amount, the distance between the ship and the cell and the distance between the cell and the closest dropoff or shipyard
Position HarvestingState::computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map)
{
  Position bestPositionTemp = Position(0, 0);
  int maxHalite = 0;
  for (int x = 0; x < game_map->getWidth(); ++x)
  {
    for (int y = 0; y < game_map->getHeight(); ++y)
    {
      MapCell *mapCell = game_map->at(Position(x, y));
      int distance = game_map->computeManathanDistance(start_pos, mapCell->getPosition());
      //To avoid division by 0
      if (distance == 0)
      {
        continue;
      }
      if (((mapCell->getHalite() / (game_map->computeManathanDistance(start_pos, mapCell->getPosition()) * DISTANCE_WEIGHT)) / (distanceToClosestDropoff(mapCell->getPosition(), game_map) * DROPOFF_DISTANCE_WEIGHT)) > maxHalite && mapCell->isOccupied() == false)
      {
        bestPositionTemp = Position(x, y);
        maxHalite = (mapCell->getHalite() / (game_map->computeManathanDistance(start_pos, mapCell->getPosition()) * DISTANCE_WEIGHT)) / (distanceToClosestDropoff(mapCell->getPosition(), game_map) * DROPOFF_DISTANCE_WEIGHT);
      }
    }
  }
  // custom_logger::log("[HarvestingState::computeBestDestination] Best Pos : " + bestPositionTemp.to_string());
  return bestPositionTemp;
}

//Return the distance to the closest dropoff to use it as a weight in the best destination computing
int HarvestingState::distanceToClosestDropoff(Position &start_pos, std::shared_ptr<GameMap> &game_map)
{
  int minDistance = INT_MAX;
  for (int x = 0; x < game_map->getWidth(); ++x)
  {
    for (int y = 0; y < game_map->getHeight(); ++y)
    {
      MapCell *mapCell = game_map->at(Position(x, y));
      if (mapCell->hasDropoff() || mapCell->hasShipyard())
      {
        if (game_map->computeManathanDistance(start_pos, mapCell->getPosition()) < minDistance)
        {
          // custom_logger::log("Dropoff found at " + Position(mapCell->getPosition().getXCoord(),mapCell->getPosition().getYCoord()).to_string());
          minDistance = game_map->computeManathanDistance(start_pos, mapCell->getPosition());
        }
      }
    }
  }
  //As the distance is used as a weight this will avoid divisions by 0
  if (minDistance == 0)
  {
    return 1;
  }
  return minDistance;
}

// Getter
Position HarvestingState::getDestination()
{
  return m_bestPosition;
}