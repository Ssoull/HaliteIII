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

Direction Ship::computeNextDirection(const Position &dest, shared_ptr<GameMap> &game_map) const
{
  m_pathToDest->initWithPosition(m_position, dest);

  //comment on l'appelle avec les paramètres ici ? 
  //Bon move d'ajouter les deux pramètres aussi en signaturede computeNextDirection
  std::vector<Position> unsafeCells = game_map->getUnsafeCells(true, true);

  custom_logger::log("[Ship::computeNextDirection] Ship id : " + std::to_string(m_entityId));
  custom_logger::log("[Ship::computeNextDirection] Current cell : " + m_position.to_string());
  custom_logger::log("[Ship::computeNextDirection] Destination cell : " + dest.to_string());

  for (int i = 0; i < unsafeCells.size(); ++i)
  {
    if (m_position != unsafeCells[i])
    {
      m_pathToDest->updateCell(unsafeCells[i].getXCoord(), unsafeCells[i].getYCoord(), -1);
      custom_logger::log("[Ship::computeNextDirection] Unsafe Cells : " + unsafeCells[i].to_string());
    }
  }

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

  custom_logger::log("[Ship::computeNextDirection] Next Step : " + std::to_string(nextStep.x) + ", " + std::to_string(nextStep.y) + ", ID SHIP : " + std::to_string(m_entityId));

  game_map->at(m_position)->markShip(true);

  int tempX = nextStep.x - m_position.getXCoord();
  int tempY = nextStep.y - m_position.getYCoord();
  if (tempX != 0)
  {
    if (tempX < 0)
    {
      return Direction::West;
    }
    else
    {
      return Direction::East;
    }
  }

  if (tempY != 0)
  {
    if (tempY < 0)
    {
      return Direction::North;
    }
    else
    {
      return Direction::South;
    }
  }

  return Direction::Still;
}

std::string Ship::stayStill() const
{
  return Command::move(m_entityId, Direction::Still);
}

std::shared_ptr<Ship> Ship::generate(const int playerId, const int game_width, const int game_height)
{
  int ship_id, x, y, halite;
  input::get_sstream() >> ship_id >> x >> y >> halite;
  return std::make_shared<Ship>(playerId, ship_id, Position(x, y), halite, game_width, game_height);
}

void Ship::update(const Ship *ship)
{
  m_shipState->update(this);
  m_halite = ship->m_halite;
  m_position = ship->m_position;
}

//Setters


void Ship::setState(State *nextState)
{
  m_shipState->onStateExit();
  m_shipState = nextState;
  m_shipState->onStateEnter();
}

// Getter
std::string Ship::getMove(){
  custom_logger::log("ntm");
  // return Command::move(m_entityId, computeNextDirection(m_position, m_game_map));
  return Command::move(m_entityId, Direction::North);
}

bool Ship::isFull() const
{
  return m_halite >= constants::MAX_HALITE;
}

int Ship::getHalite() const
{
  return m_halite;
}
