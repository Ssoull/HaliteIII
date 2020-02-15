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

  // Getter
  bool isEmpty() const;
  bool isOccupied() const;
  bool hasStructure() const;
  int getHalite() const;

  // Setter
  void setHalite(const int halite);
  void markShip(const bool hasShip);
  void markStructure(const bool hasStructure);
};

#endif