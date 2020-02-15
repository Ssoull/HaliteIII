#include "player.hpp"
#include "input.hpp"

#include <memory>

Player::Player(const int playerId, const Position &pos) : m_id(playerId), m_halite(0), m_shipyard(std::make_shared<Shipyard>(playerId, pos)) {}

void Player::update(const int numShips, const int numDropoffs, const int halite)
{
  m_halite = halite;

  m_ships.clear();
  for (int i = 0; i < numShips; ++i) {
    std::shared_ptr<Ship> ship = Ship::generate(m_id);
    m_ships[ship->getId()] = ship;
  }

  m_dropoffs.clear();
  for (int i = 0; i < numDropoffs; ++i) {
    std::shared_ptr<Dropoff> dropoff = Dropoff::generate(m_id);
    m_dropoffs[dropoff->getId()] = dropoff;
  }
}

std::shared_ptr<Player> Player::generate()
{
  int player_id;
  int shipyard_x;
  int shipyard_y;
  input::get_sstream() >> player_id >> shipyard_x >> shipyard_y;

  return std::make_shared<Player>(player_id, Position(shipyard_x, shipyard_y));
}

// Getter
std::unordered_map<int, std::shared_ptr<Ship>> Player::getShips() const
{
  return m_ships;
}

std::unordered_map<int, std::shared_ptr<Dropoff>> Player::getDropoffs() const
{
    return m_dropoffs;
}

std::shared_ptr<Shipyard> Player::getShipyard() const
{
  return m_shipyard;
}

int Player::getHalite(){
  return m_halite;
}
