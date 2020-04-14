#include "player.hpp"

#include "../utils/input.hpp"

#include <memory>

Player::Player(const int player_id, const Position &pos) : m_id(player_id), m_halite(0), m_shipyard(std::make_shared<Shipyard>(player_id, pos)) {}

void Player::update(const int num_ships, const int num_dropoffs, const int halite, const int game_width, const int game_height)
{
  m_halite = halite;
  m_dropoffThisTurn = false;
  updateShips(num_ships, game_width, game_height);
  updateDropoffs(num_dropoffs);
}

void Player::updateShips(const int num_ships, const int game_width, const int game_height)
{
  std::vector<int> id_ships;

  // Create or update ships
  for (int i = 0; i < num_ships; ++i)
  {
    std::shared_ptr<Ship> ship = Ship::generate(m_id, game_width, game_height);
    id_ships.push_back(ship->getId());

    // If there is no ship with this id, we add him to the vector
    if (m_ships.find(ship->getId()) == m_ships.end())
    {
      m_ships[ship->getId()] = ship;
      custom_logger::log("[Player::updateShips] Ship created, id " + std::to_string(ship->getId()));
    }
    else
    {
      m_ships[ship->getId()]->update(ship.get());
      custom_logger::log("[Player::updateShips] Ship updated, id " + std::to_string(ship->getId()));
    }
  }

  // Delete destroyed ship
  for (auto it = m_ships.begin(); it != m_ships.end();)
  {
    if (std::find(id_ships.begin(), id_ships.end(), it->first) == id_ships.end())
    {
      it = m_ships.erase(it);
      custom_logger::log("[Player::updateShips] Ship erased, id : " + std::to_string(it->first));
    }
    else
    {
      ++it;
    }
  }
}

void Player::updateDropoffs(const int num_dropoffs)
{
  std::vector<int> id_dropoffs;

  // Create dropoff
  for (int i = 0; i < num_dropoffs; ++i)
  {
    std::shared_ptr<Dropoff> dropoff = Dropoff::generate(m_id);
    id_dropoffs.push_back(dropoff->getId());

    // If there is no dropoff with this id, we add him to the vector
    if (m_dropoffs.find(dropoff->getId()) == m_dropoffs.end())
    {
      m_dropoffs[dropoff->getId()] = dropoff;
      custom_logger::log("[Player::updateDropoffs] Dropoff created, id " + std::to_string(dropoff->getId()));
    }
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

int Player::getHalite() const
{
  return m_halite;
}

int Player::getId() const
{
  return m_id;
}

bool Player::getDropoffCreation() const
{
  return m_dropoffThisTurn;
}

void Player::setDropoffCreation(bool ff)
{
  m_dropoffThisTurn = ff;
}