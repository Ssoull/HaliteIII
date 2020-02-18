#ifndef SHIP_H
#define SHIP_H

#include "entity.hpp"
#include "position.hpp"

#include "../utils/command.hpp"

#include "../state/state.hpp"

class Ship : public Entity
{
private:
  int m_halite;
  State *m_shipState;

public:
  Ship(const int ownerId, const int entityId, const Position &pos, const int halite);

  // Action
  std::string makeDropoff() const;

  std::string move(const Direction direction) const;
  std::string stayStill() const;

  static std::shared_ptr<Ship> generate(const int playerID);
  void update(const Ship *ship);
  void setState(State *nextState);

  // Getter
  bool isFull();
};

#endif