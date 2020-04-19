#include "dropState.hpp"
#include "../utils/log.hpp"
#include "harvestingState.hpp"

void DropState::update(Ship *entity_to_update, std::shared_ptr<GameMap> &game_map)
{
  //Check when the ship has arrived to the dropoff creation place
  if (willBeDropoff && entity_to_update->getPosition() == m_bestDropLocation)
  {
    shouldCreateDropoff = true;
    //Even if the ship is on the dropoff location the conditions to create it may not be matched
    //Every turn the ship is stuck in place it will check for a dropoff with a larger radius
    //If a dropoff is found before the requirements to create a dropoff are met it will head to this dropoff
    if (checkForDropoff(game_map, DROPOFF_CHECK_RADIUS + m_nbOfTurnsStuck, entity_to_update->getPosition()))
    {
      m_bestDropLocation = m_dropoffLocation;
      shouldCreateDropoff = false;
    }
    else
    {
      m_nbOfTurnsStuck++;
    }
  }

  //When the ship is empty it will return to the harvesting state
  if (entity_to_update->getHalite() == 0)
  {
    // custom_logger::log("Halite Dropped, going to harvest");
    entity_to_update->setState(std::make_shared<HarvestingState>(), game_map);
  }
}

void DropState::onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity)
{
  //Check if there is a dropoff in surrondings
  // custom_logger::log("Entering drop state");
  if (checkForDropoff(game_map, DROPOFF_CHECK_RADIUS, entity->getPosition()))
  {
    m_bestDropLocation = m_dropoffLocation;
  }
  else
  {
    //When no dropoff found the ship will become a dropoff
    willBeDropoff = true;
    m_bestDropLocation = computeBestDestination(entity->getPosition(), game_map);
  }
}

void DropState::onStateExit()
{
}

Position DropState::getDestination()
{
  return m_bestDropLocation;
}

//Used when no dropoff is found to find the best place to create a dropoff
Position DropState::computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map)
{
  Position bestPosition = Position(0, 0);
  int maxHalite = 0;
  for (int i = 0; i < game_map->getWidth(); ++i)
  {
    for (int j = 0; j < game_map->getHeight(); ++j)
    {
      MapCell *mapCell = game_map->at(Position(i, j));
      if (mapCell->getHalite() > maxHalite && game_map->computeManathanDistance(mapCell->getPosition(), start_pos) < DROPOFF_CHECK_RADIUS)
      {
        maxHalite = mapCell->getHalite();
        bestPosition = Position(mapCell->getPosition().getXCoord(), mapCell->getPosition().getYCoord());
      }
    }
  }
  return bestPosition;
}

bool DropState::checkForDropoff(std::shared_ptr<GameMap> &game_map, int radius, Position center)
{
  // custom_logger::log("Checking fro dropoff");
  std::vector<Position> positionsInRadius = game_map->getPositionsInRadius(center, radius);
  for (int i = 0; i < positionsInRadius.size(); ++i)
  {
    MapCell *mapCell = game_map->at(positionsInRadius[i]);
    if ((mapCell->hasDropoff() || mapCell->hasShipyard()) && mapCell->isMine())
    {
      m_dropoffLocation = positionsInRadius[i];
      return true;
    }
  }
  // custom_logger::log("Dropoff not found");
  return false;
}
