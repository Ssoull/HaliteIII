#include "map_cell.hpp"

MapCell::MapCell(const Position &pos, const int halite) : m_position(pos), m_halite(halite) {}

// Getter
bool MapCell::isEmpty() const
{
  return !m_hasShip || !m_hasStructure;
}

bool MapCell::isOccupied() const
{
  return m_hasShip;
}

bool MapCell::hasStructure() const
{
  return m_hasStructure;
}

int MapCell::getHalite() const
{
  return m_halite;
}

// Setter
void MapCell::setHalite(const int halite)
{
  m_halite = halite;
}

void MapCell::markShip(bool hasShip)
{
  m_hasShip = hasShip;
}

void MapCell::markStructure(bool hasStructure)
{
  m_hasStructure = hasStructure;
}