#ifndef SHIP_H
#define SHIP_H

#include "dstar.hpp"
#include "game_map.hpp"

#include "../utils/command.hpp"

#include "../state/state.hpp"

class State;

class Ship : public Entity
{
private:
  int m_halite;
  std::shared_ptr<State> m_shipState;
  std::unique_ptr<Dstar> m_pathToDest;

  Direction directionSelection(const int diff, const int size, const Direction first, const Direction second) const;
  void populateDstar(std::shared_ptr<GameMap> &game_map, const bool include_shipyard, const bool include_dropoffs /*, const double costToMove*/);

public:
  Ship(const int ownerId, const int entityId, const Position &pos, const int halite, const int game_width, const int game_height);

  // Action
  std::string makeDropoff() const;

  std::string move(const Direction direction) const;
  Direction computeNextDirection(const Position &position, std::shared_ptr<GameMap> &game_map, const bool include_shipyard, const bool include_dropoffs);
  std::string stayStill() const;

  static std::shared_ptr<Ship> generate(const int playerID, const int game_width, const int game_height);

  void init();

  void update(const Ship *ship);

  // Update function used in main
  // use the game map as paramteter to compute best actions the ship can perform
  std::string update(std::shared_ptr<GameMap> &game_map);

  void setState(std::shared_ptr<State> nextState, std::shared_ptr<GameMap> &game_map);

  // Getter
  bool isFull() const;
  int getHalite() const;
};

#endif