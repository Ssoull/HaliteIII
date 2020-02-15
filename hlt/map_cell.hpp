#ifndef MAPCELL_H
#define MAPCELL_H

#include "position.hpp"

class MapCell
{
private:
  Position m_position;
  int m_halite;

  bool m_hasShip;
  bool m_hasStructure;

public:
  MapCell(const Position &pos, const int halite);

  void markShip(const bool hasShip);
  void markStructure(const bool hasStructure);

  // Getter
  bool isEmpty() const;
  bool isOccupied() const;
  bool hasStructure() const;

  // Setter
  int setHalite(const int halite);
};

#endif