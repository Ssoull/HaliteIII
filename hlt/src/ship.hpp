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
  Direction m_nextMove;
  Position m_destination;

  Direction directionSelection(const int diff, const int size, const Direction first, const Direction second) const;

public:
  Ship(const int ownerId, const int entityId, const Position &pos, const int halite, const int game_width, const int game_height);

  // Action
  std::string makeDropoff() const;

  std::string move(const Direction direction) const;
  Direction computeNextDirection(const Position &position, std::shared_ptr<GameMap> &game_map) const;
  std::string stayStill() const;

  //Update function used in main
  //use the game map as paramteter to compute best actions the ship can perform
  std::string update(std::shared_ptr<GameMap> &game_map);
  
  
  static std::shared_ptr<Ship> generate(const int playerID, const int game_width, const int game_height);


  //Ca sert à quoi de mettre le ship en paramètre ?
  //Y'a pas moyen de faire sans dans le player ? 
  void update(const Ship *ship);
  // void update();
  void setState(State *nextState);

  // Getter
  bool isFull() const;
  int getHalite() const;
  
};

#endif