#include "ship.hpp"

#include "../utils/constants.hpp"
#include "../utils/input.hpp"

#include "../state/harvestingState.hpp"

Ship::Ship(const int ownerId, const int entityId, const Position &pos, const int halite) : Entity(ownerId, entityId, pos), m_halite(halite), m_shipState(new HarvestingState()) {}

// Action
std::string Ship::makeDropoff() const
{
  return Command::transformShipIntoDropoff(m_entityId);
}

std::string Ship::move(const Direction direction) const
{
  return Command::move(m_entityId, direction);
}

std::string Ship::stayStill() const
{
  return Command::move(m_entityId, Direction::Still);
}

std::shared_ptr<Ship> Ship::generate(const int playerId)
{
  int ship_id, x, y, halite;
  input::get_sstream() >> ship_id >> x >> y >> halite;
  return std::make_shared<Ship>(playerId, ship_id, Position(x, y), halite);
}

void Ship::update(const Ship *ship)
{
  m_shipState->update(this);
  m_halite = ship->m_halite;
  m_position = ship->m_position;
}

void Ship::setState(State *nextState)
{
  m_shipState->onStateExit();
  m_shipState = nextState;
  m_shipState->onStateEnter();
}

// Getter
bool Ship::isFull()
{
  return m_halite >= constants::MAX_HALITE;
}