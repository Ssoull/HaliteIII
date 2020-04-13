#include "map_cell.hpp"

MapCell::MapCell() {}

MapCell::MapCell(const Position &pos, const int halite) : m_position(pos),
                                                          m_halite(halite),
                                                          m_isMine(false),
                                                          m_hasShip(false),
                                                          m_hasShipyard(false),
                                                          m_hasDropoff(false)
{
}

// Getter
bool MapCell::isEmpty() const
{
  return !m_hasShip || !m_hasDropoff || !m_hasShipyard;
}

bool MapCell::isOccupied() const
{
  return m_hasShip || m_hasShipyard || m_hasDropoff;
}

bool MapCell::hasStructure() const
{
  return m_hasShipyard || m_hasDropoff;
}

bool MapCell::hasShip() const
{
  return m_hasShip;
}

bool MapCell::hasShipyard() const
{
  return m_hasShipyard;
}

bool MapCell::hasDropoff() const
{
  return m_hasDropoff;
}

int MapCell::getHalite() const
{
  return m_halite;
}

Position MapCell::getPosition() const
{
  return m_position;
}

bool MapCell::isMine() const
{
  return m_isMine;
}

// Setter
void MapCell::setHalite(const int halite)
{
  m_halite = halite;
}

void MapCell::markShip(const bool hasShip, const bool isMine)
{
  m_hasShip = hasShip;
}

void MapCell::markShipyard(const bool hasShipyard, const bool isMine)
{
  m_hasShipyard = hasShipyard;
}

void MapCell::markDropoff(const bool hasDropoff, const bool isMine)
{
  m_hasDropoff = hasDropoff;
}