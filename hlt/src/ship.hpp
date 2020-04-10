#ifndef SHIP_H
#define SHIP_H

#include "dstar.hpp"
#include "game_map.hpp"

#include "../utils/command.hpp"

#include "../state/state.hpp"

class Ship : public Entity
{
private:
  int m_halite;
  State *m_shipState;
  std::unique_ptr<Dstar> m_pathToDest;

public:
  Ship(const int ownerId, const int entityId, const Position &pos, const int halite, const int game_width, const int game_height);

  // Action
  std::string makeDropoff() const;

  std::string move(const Direction direction) const;
  Direction computeNextDirection(const Position &position, shared_ptr<GameMap> &game_map) const;
  std::string stayStill() const;

  static std::shared_ptr<Ship> generate(const int playerID, const int game_width, const int game_height);
  void update(const Ship *ship);
  void setState(State *nextState);

  // Getter
  bool isFull() const;
  int getHalite() const;
};

#endif