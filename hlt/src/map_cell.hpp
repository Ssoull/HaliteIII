#ifndef MAPCELL_H
#define MAPCELL_H

#include "position.hpp"

class MapCell
{
private:
  Position m_position;
  int m_halite;

  bool m_isMine;

  bool m_hasShip;
  bool m_hasShipyard;
  bool m_hasDropoff;

public:
  MapCell();
  MapCell(const Position &pos, const int halite);

  // Getter
  bool isEmpty() const;
  bool isOccupied() const;
  bool hasStructure() const;
  bool hasShip() const;
  bool hasShipyard() const;
  bool hasDropoff() const;
  int getHalite() const;
  Position getPosition() const;
  bool isMine() const;

  // Setter
  void setHalite(const int halite);
  void markShip(const bool hasShip, const bool isMine);
  void markShipyard(const bool hasShip, const bool isMine);
  void markDropoff(const bool hasDropoff, const bool isMine);
};

#endif