#include "ship.hpp"

#include "../utils/constants.hpp"
#include "../utils/input.hpp"

#include "../state/harvestingState.hpp"

Ship::Ship(const int ownerId, const int entityId, const Position &pos, const int halite, const int game_width, const int game_height) : Entity(ownerId, entityId, pos),
                                                                                                                                        m_halite(halite),
                                                                                                                                        m_shipState(new HarvestingState()),
                                                                                                                                        m_pathToDest(std::unique_ptr<Dstar>(new Dstar(game_width, game_height)))
// m_game_map(shared_ptr<GameMap>(new GameMap()))
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

Direction Ship::computeNextDirection(const Position &dest, std::shared_ptr<GameMap> &game_map, const int include_shipyard, const int include_dropoffs) const
{
  m_pathToDest->init(m_position, dest);

  custom_logger::log("[Ship::computeNextDirection] Ship id : " + std::to_string(m_entityId));
  custom_logger::log("[Ship::computeNextDirection] Current cell : " + m_position.to_string());
  custom_logger::log("[Ship::computeNextDirection] Destination cell : " + dest.to_string());

  game_map->populateDstar(m_pathToDest.get(), m_position, include_shipyard, include_dropoffs);

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

  custom_logger::log("[Ship::computeNextDirection] Next Step : " + std::to_string(nextStep.x) + ", " + std::to_string(nextStep.y) + ", ID ship : " + std::to_string(m_entityId));

  game_map->at(Position(nextStep.x, nextStep.y))->markShip(true);

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
  return Command::move(m_entityId, computeNextDirection(m_shipState->getDestination(), game_map, false, false));
}

//Setters

void Ship::setState(State *nextState)
{
  m_shipState->onStateExit();
  m_shipState = nextState;
  m_shipState->onStateEnter();
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
