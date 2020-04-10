#ifndef PLAYER_H
#define PLAYER_H

#include "shipyard.hpp"
#include "ship.hpp"
#include "dropoff.hpp"

#include <unordered_map>

class Player
{
private:
  int m_id;
  int m_halite;
  std::shared_ptr<Shipyard> m_shipyard;

  std::unordered_map<int, std::shared_ptr<Ship>> m_ships;
  std::unordered_map<int, std::shared_ptr<Dropoff>> m_dropoffs;

public:
  Player(const int playerId, const Position &pos);

  void update(const int numShips, const int numDropoffs, const int halite, const int game_width, const int game_height);
  void updateShips(const int numShips, const int game_width, const int game_height);
  void updateDropoffs(const int numDropoffs);
  static std::shared_ptr<Player> generate();

  // Getter
  std::unordered_map<int, std::shared_ptr<Ship>> getShips() const;
  std::unordered_map<int, std::shared_ptr<Dropoff>> getDropoffs() const;
  std::shared_ptr<Shipyard> getShipyard() const;
  int getHalite();
};

#endif