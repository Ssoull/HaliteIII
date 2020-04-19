#ifndef PLAYER_H
#define PLAYER_H

#include "shipyard.hpp"
#include "ship.hpp"
#include "dropoff.hpp"

#include <unordered_map>

// These class are init later
class Ship;

// Player class
class Player
{
private:
  int m_id;
  int m_halite;
  std::shared_ptr<Shipyard> m_shipyard;
  bool m_dropoffThisTurn = false;

  std::unordered_map<int, std::shared_ptr<Ship>> m_ships;       // Unordered Map of all the player's ships
  std::unordered_map<int, std::shared_ptr<Dropoff>> m_dropoffs; // Unordered Map of all the player's dropoffs

public:
  Player(const int playerId, const Position &pos);

  void update(const int num_ships, const int num_dropoffs, const int halite, const int game_width, const int game_height);
  void updateShips(const int num_ships, const int game_width, const int game_height);
  void updateDropoffs(const int num_dropoffs);
  static std::shared_ptr<Player> generate();

  void Player::setDropoffCreation(bool ff);

  // Getter
  std::unordered_map<int, std::shared_ptr<Ship>> getShips() const;
  std::unordered_map<int, std::shared_ptr<Dropoff>> getDropoffs() const;
  std::shared_ptr<Shipyard> getShipyard() const;
  int getHalite() const;
  int getId() const;
  bool getDropoffCreation() const;
};

#endif