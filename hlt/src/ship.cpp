#include "ship.hpp"

#include "../utils/constants.hpp"
#include "../utils/input.hpp"

#include "../state/harvestingState.hpp"
#include "../state/defaultState.hpp"

Ship::Ship(const int ownerId, const int entityId, const Position &pos, const int halite, const int game_width, const int game_height) : Entity(ownerId, entityId, pos),
                                                                                                                                        m_halite(halite),
                                                                                                                                        m_shipState(std::make_shared<DefaultState>()),
                                                                                                                                        m_pathToDest(std::make_unique<Dstar>(game_width, game_height))
{
}

// Action
std::string Ship::makeDropoff() const
{
  return Command::transformShipIntoDropoff(m_entityId);
}

std::string Ship::move(const Direction direction) const
{
  return Command::move(m_entityId, direction);
}

Direction Ship::computeNextDirection(const Position &dest, std::shared_ptr<GameMap> &game_map,
                                     const bool include_shipyard, const bool include_dropoffs)
{
  custom_logger::log("[Ship::computeNextDirection] Ship id : " + std::to_string(m_entityId));
  custom_logger::log("[Ship::computeNextDirection] Current cell : " + m_position.to_string());
  custom_logger::log("[Ship::computeNextDirection] Destination cell : " + dest.to_string());

  // Check if the ship have enough halite to move
  double costToMove = game_map->getCost(m_position);
  if (m_halite < costToMove) // Must not be equal because if current halite=0 and cost=0, the ship can move
  {
    custom_logger::log("[Ship::computeNextDirection] Not enough halite : " + std::to_string(m_halite) + ", Cost to move : " + std::to_string(costToMove));
    return Direction::Still;
  }

  m_pathToDest->init(m_position, dest);

  populateDstar(game_map, include_shipyard, include_dropoffs);

  if (!m_pathToDest->replan())
  {
    return Direction::Still;
  }

  list<state> list = m_pathToDest->getPath();
  list.pop_front();

  state nextStep;

  if (!list.empty())
  {
    nextStep = list.front();
  }
  else
  {
    nextStep.x = m_position.getXCoord();
    nextStep.y = m_position.getYCoord();
  }

  custom_logger::log("[Ship::computeNextDirection] Next Step : " + std::to_string(nextStep.x) + ", " +
                     std::to_string(nextStep.y) + ", ID ship : " + std::to_string(m_entityId));

  game_map->at(Position(nextStep.x, nextStep.y))->markShip(true, true);

  int dx = nextStep.x - m_position.getXCoord();
  if (dx != 0)
  {
    return directionSelection(dx, game_map->getWidth(), Direction::East, Direction::West);
  }

  int dy = nextStep.y - m_position.getYCoord();
  if (dy != 0)
  {
    return directionSelection(dy, game_map->getHeight(), Direction::South, Direction::North);
  }

  return Direction::Still;
}

// Private function & method

Direction Ship::directionSelection(const int diff, const int size, const Direction first, const Direction second) const
{
  if (abs(diff) > size / 2)
  {
    if (diff < 0)
    {
      return first;
    }
    else
    {
      return second;
    }
  }
  else
  {
    if (diff < 0)
    {
      return second;
    }
    else
    {
      return first;
    }
  }
}

void Ship::populateDstar(std::shared_ptr<GameMap> &game_map, const bool include_shipyard, const bool include_dropoffs)
{

  for (int x = 0; x < game_map->getWidth(); ++x)
  {
    for (int y = 0; y < game_map->getHeight(); ++y)
    {
      Position currentPosition = Position(x, y);
      MapCell currentMapCell = *game_map->at(currentPosition);

      if (!currentMapCell.hasStructure())
      {
        // To debug the cost on each cell
        // Commented by default otherwise there is to much data displayed in logs
        // custom_logger::log("[Ship::populateDstar] Move cost at : " + currentPosition.to_string() + " - cost : " +
        //                    std::to_string(game_map->getCost(currentPosition) / 100));
        m_pathToDest->updateCell(currentPosition, game_map->getCost(currentPosition) / 100);
      }

      if (m_position != currentPosition && currentMapCell.isOccupied())
      {
        // Check if the cell has a shipyard on it
        // If yes and if we want to include the shipyard in unsafe cells it's added to the list
        bool hasShipyard = currentMapCell.hasShipyard() && include_shipyard ? true : false;

        // Check for dropoffs if the dropoffs are included in the cells to mark as unsafe
        bool hasDropoff = currentMapCell.hasDropoff() && include_dropoffs ? true : false;

        // Check for other ships
        bool hasShip = currentMapCell.hasShip() ? true : false;

        if (hasShipyard || hasDropoff || hasShip)
        {
          m_pathToDest->updateCell(currentPosition, -1);
          custom_logger::log("[GameMap::populateDstar] Unsafe Cells : " + currentPosition.to_string());
        }
      }
    }
  }
}

// End zone private function & method

std::string Ship::stayStill() const
{
  return Command::move(m_entityId, Direction::Still);
}

shared_ptr<Ship> Ship::generate(const int playerId, const int game_width, const int game_height)
{
  int ship_id, x, y, halite;
  input::get_sstream() >> ship_id >> x >> y >> halite;
  return std::make_shared<Ship>(playerId, ship_id, Position(x, y), halite, game_width, game_height);
}

void Ship::update(const Ship *ship)
{
  m_halite = ship->m_halite;
  m_position = ship->m_position;
}

std::string Ship::update(shared_ptr<GameMap> &game_map)
{
  m_shipState->update(this, game_map);
  //TODO: Trouver un moyen de faire en sorte de savoir si on doit inclure ou non les shipyard/dropoffs
  if (!m_shipState->shouldCreateDropoff)
  {
    return Command::move(m_entityId, computeNextDirection(m_shipState->getDestination(), game_map, true, true));
  }
  else
  {
    custom_logger::log("Transforming ship");
    // return Command::transformShipIntoDropoff(m_entityId);
    return Command::move(m_entityId, Direction::Still);
  }
}

//Setters
void Ship::setState(std::shared_ptr<State> nextState, std::shared_ptr<GameMap> &game_map)
{
  m_shipState->onStateExit();
  m_shipState = nextState;
  m_shipState->onStateEnter(game_map, this);
}

// Getter

bool Ship::isFull() const
{
  return m_halite >= constants::MAX_HALITE;
}

int Ship::getHalite() const
{
  return m_halite;
}
