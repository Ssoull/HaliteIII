#include "dropState.hpp"
#include "../utils/log.hpp"
#include "harvestingState.hpp"

void DropState::update(Ship *entity_to_update, std::shared_ptr<GameMap> &game_map)
{
	//Check when the ship has arrived to the dropoff creation place
	if (willBeDropoff && entity_to_update->getPosition() == m_bestDropLocation)
	{
		shouldCreateDropoff = true;
	}

	if (entity_to_update->getHalite() == 0)
	{
        custom_logger::log("Halite Dropped, goind to harvest");
		entity_to_update->setState(std::make_shared<HarvestingState>(), game_map);
	}
}

void DropState::onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity)
{
	//Check if there is a dropoff in surrondings
	custom_logger::log("Entering drop state");
	if (checkForDropoff(game_map, DROPOFF_CHECK_RADIUS, entity->getPosition()))
	{
		m_bestDropLocation = m_dropoffLocation;
	}
	else
	{
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

Position DropState::computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map)
{
	return Position(0, 0);
}

bool DropState::checkForDropoff(std::shared_ptr<GameMap> &game_map, int radius, Position center)
{
	custom_logger::log("Checking fro dropoff");
	std::vector<Position> positionsInRadius = game_map->getPositionsInRadius(center, radius);
	for (int i = 0; i < positionsInRadius.size(); ++i)
	{
		MapCell *mapCell = game_map->at(positionsInRadius[i]);
		if ((mapCell->hasDropoff() || mapCell->hasShipyard()) && mapCell->isMine())
		{
			// if(game_map->at(positionsInRadius[i])->)
			m_dropoffLocation = positionsInRadius[i];
            custom_logger::log("Dropoff found "+ m_dropoffLocation.to_string());
			return true;
		}
	}
	custom_logger::log("Dropoff not found");
	return false;
}
